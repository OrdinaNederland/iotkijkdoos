package nl.ordina.kijkdoos;

import android.os.Bundle;
import android.os.Parcelable;
import android.support.annotation.VisibleForTesting;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.AppCompatActivity;
import android.view.Gravity;
import android.widget.ImageView;

import org.parceler.Parcels;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnCheckedChanged;
import butterknife.OnClick;
import lombok.AccessLevel;
import lombok.Getter;
import nl.ordina.kijkdoos.bluetooth.ViewBoxRemoteController;

import static nl.ordina.kijkdoos.ViewBoxApplication.getViewBoxApplication;

public class ViewBoxActivity extends AppCompatActivity {

    public static final String EXTRA_KEY_BUNDLED_VIEW_BOX_REMOTE_CONTROLLER = "BUNDLED_VIEW_BOX_REMOTE_CONTROLLER";
    public static final String EXTRA_KEY_VIEW_BOX_REMOTE_CONTROLLER = "VIEW_BOX_REMOTE_CONTROLLER";

    @BindView(R.id.ivTelevision)
    public ImageView television;

    @BindView(R.id.component_controller)
    public DrawerLayout componentController;

    @BindView(R.id.ivLeftLamp)
    public ImageView ivLeftLamp;

    @Getter(AccessLevel.PACKAGE) @VisibleForTesting
    private ViewBoxRemoteController viewBoxRemoteController;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_view_box);
        ButterKnife.bind(this);
        getViewBoxApplication(this).getApplicationComponent().inject(this);

        final Bundle bundledExtras = getIntent().getExtras();
        final Bundle actualExtras = bundledExtras.getBundle(EXTRA_KEY_BUNDLED_VIEW_BOX_REMOTE_CONTROLLER);

        final Parcelable parceledViewBoxRemoteController = actualExtras.getParcelable(EXTRA_KEY_VIEW_BOX_REMOTE_CONTROLLER);
        viewBoxRemoteController = Parcels.unwrap(parceledViewBoxRemoteController);
        viewBoxRemoteController.connect(this);
    }

    @Override
    protected void onPause() {
        viewBoxRemoteController.disconnect();
        super.onPause();
    }

    @OnClick(R.id.ivTelevision)
    public void onTelevisionClicked() {

    }

    @OnClick(R.id.ivLeftLamp)
    public void onLeftLampClicked() {
        componentController.openDrawer(Gravity.LEFT);
    }

    @OnCheckedChanged(R.id.switchLight)
    public void onLightSwitchChanged() {
        viewBoxRemoteController.toggleLed();
    }
}
