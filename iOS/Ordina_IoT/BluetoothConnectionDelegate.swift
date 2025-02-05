//
//  DelegateTest.swift
//  BLE_punchpad
//
//  Created by Rik Wout on 22-10-16.
//  Copyright © 2016 Wo. All rights reserved.
//

import UIKit
import CoreBluetooth

var bluetooth: BluetoothConnection!

protocol BluetoothConnectionDelegate    {
    func bluetoothDidChangeState(_ central: CBCentralManager)
    func bluetoothDidDiscoverPeripheral(_ peripheral: CBPeripheral, RSSI: NSNumber?)
    func bluetoothDidConnect(_ peripheral: CBPeripheral)
    func bluetoothDidDisconnect(_ peripheral: CBPeripheral, error: NSError?)
    func bluetoothDidFailToConnect(_ peripheral: CBPeripheral, error: NSError?)
    func bluetoothDidReceiveString(_ message: String)
}

extension BluetoothConnectionDelegate   {
    func bluetoothDidDiscoverPeripheral(_ peripheral: CBPeripheral, RSSI: NSNumber?){}
    func bluetoothDidConnect(_ peripheral: CBPeripheral){}
    func bluetoothDidDisconnect(_ peripheral: CBPeripheral, error: NSError?){}
    func bluetoothDidFailToConnect(_ peripheral: CBPeripheral, error: NSError?){}
    func bluetoothDidReceiveString(_ message: String){}
}

final class BluetoothConnection: NSObject, CBCentralManagerDelegate, CBPeripheralDelegate   {
    
    private enum UUID   {
        static let service = CBUUID(string: "FFE0")
        static let characteristic = CBUUID(string: "FFE1")
    }
    
    var delegate: BluetoothConnectionDelegate?
    var manager: CBCentralManager!
    private(set) var connectedPeripheral: CBPeripheral?
    weak var writeCharacteristic: CBCharacteristic?
    private var writeType: CBCharacteristicWriteType = .withoutResponse
    
    var isReady: Bool {
        get {
            return manager.state == .poweredOn &&
                connectedPeripheral != nil &&
                writeCharacteristic != nil
        }
    }
    
    init(delegate: BluetoothConnectionDelegate) {
        super.init()
        self.delegate = delegate
        manager = CBCentralManager(delegate: self, queue: nil)
    }
    
    
//Central Manager
    
    func centralManagerDidUpdateState(_ central: CBCentralManager) {
        delegate?.bluetoothDidChangeState(central)
    }
    
    func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral, advertisementData: [String : Any], rssi RSSI: NSNumber) {
        delegate?.bluetoothDidDiscoverPeripheral(peripheral, RSSI: RSSI)
    }
    
    func centralManager(_ central: CBCentralManager, didConnect peripheral: CBPeripheral) {
        peripheral.delegate = self      //Strong reference to keep connected
        connectedPeripheral = peripheral
        peripheral.discoverServices([UUID.service])
    }
    
    func centralManager(_ central: CBCentralManager, didFailToConnect peripheral: CBPeripheral, error: Error?) {
        connectedPeripheral = nil
        delegate?.bluetoothDidFailToConnect(peripheral, error: error as NSError?)
    }
    
    func centralManager(_ central: CBCentralManager, didDisconnectPeripheral peripheral: CBPeripheral, error: Error?) {
        connectedPeripheral = nil
        delegate?.bluetoothDidDisconnect(peripheral, error: error as NSError?)
    }
    
    
//Peripheral
    
    func peripheral(_ peripheral: CBPeripheral, didDiscoverServices error: Error?) {
        peripheral.discoverCharacteristics([UUID.characteristic], for: peripheral.services![0])
    }
    
    func peripheral(_ peripheral: CBPeripheral, didDiscoverCharacteristicsFor service: CBService, error: Error?) {
        for characteristic in service.characteristics!   {
            if characteristic.uuid == UUID.characteristic    {
                peripheral.setNotifyValue(true, for: characteristic)
            }
            writeCharacteristic = characteristic
            delegate?.bluetoothDidConnect(peripheral)
        }
    }
    
    func peripheral(_ peripheral: CBPeripheral, didUpdateValueFor characteristic: CBCharacteristic, error: Error?) {
        let data = characteristic.value
        guard data != nil else {return}
        if let message = String(data: data!, encoding: String.Encoding.utf8) {
            delegate?.bluetoothDidReceiveString(message)
        }
    }
  
    func startScanning()    {
        guard manager.state == .poweredOn else {return}
        let uuid = UUID.service
        manager.scanForPeripherals(withServices: [uuid], options: nil)
    }
    
    func stopScanning() {
        manager.stopScan()
    }
    
    
    func sendMessage(string: String)  {
        if !string.isEmpty && self.isReady {
            let data = string.data(using: String.Encoding.utf8)
            connectedPeripheral!.writeValue(data!, for: writeCharacteristic!, type: writeType)
        }
    }
}








