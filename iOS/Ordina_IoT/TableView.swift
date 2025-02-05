//
//  TableView.swift
//  Ordina_IoT
//
//  Created by Rik Wout on 13-02-17.
//  Copyright © 2017 Wo. All rights reserved.
//

import UIKit
import CoreBluetooth

protocol TableViewDelegate  {
    func userDidSelectRow(indexPath: IndexPath)
}

class TableView: NSObject, UITableViewDelegate, UITableViewDataSource     {
    
    private var tableViewData = [String]()
    private var delegate: TableViewDelegate?
 
    init(delegate: TableViewDelegate, data: [String])  {
        super.init()
        self.delegate = delegate
        self.tableViewData = data
    }
    
    func updateTableViewData(data: [String])  {
        tableViewData = data
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return tableViewData.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = UITableViewCell()
        cell.textLabel?.text = tableViewData[indexPath.row]
        cell.backgroundColor = UIColor.white
        cell.textLabel?.font = UIFont.avenirNext(size: 19)
        cell.textLabel?.textColor = UIColor.black
        cell.accessoryType = .disclosureIndicator

        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        delegate?.userDidSelectRow(indexPath: indexPath)
    }
}
