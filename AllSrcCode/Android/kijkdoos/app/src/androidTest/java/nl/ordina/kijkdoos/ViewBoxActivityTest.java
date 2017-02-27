package nl.ordina.kijkdoos;

import android.content.Intent;
import android.os.Bundle;
import android.support.test.InstrumentationRegistry;
import android.support.test.espresso.intent.rule.IntentsTestRule;
import android.support.test.runner.AndroidJUnit4;

import org.junit.Rule;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.parceler.Parcels;

import nl.ordina.kijkdoos.bluetooth.MockedViewBoxRemoteController;
import nl.ordina.kijkdoos.bluetooth.ViewBoxRemoteController;

import static android.support.test.espresso.Espresso.onView;
import static android.support.test.espresso.action.ViewActions.click;
import static android.support.test.espresso.assertion.ViewAssertions.matches;
import static android.support.test.espresso.matcher.ViewMatchers.isChecked;
import static android.support.test.espresso.matcher.ViewMatchers.isDisplayed;
import static android.support.test.espresso.matcher.ViewMatchers.isNotChecked;
import static android.support.test.espresso.matcher.ViewMatchers.withId;
import static org.mockito.Mockito.verify;

/**
 * Created by coenhoutman on 13-2-2017.
 */
@RunWith(AndroidJUnit4.class)
public class ViewBoxActivityTest {

    private ViewBoxRemoteController mockedViewBoxRemoteController;

    @Rule
    public IntentsTestRule<ViewBoxActivity> activityRule = new IntentsTestRule(ViewBoxActivity.class) {
        @Override
        protected Intent getActivityIntent() {

            final MockedViewBoxRemoteController mockedViewBoxApplication = new MockedViewBoxRemoteController();

            final Intent intent = new Intent(InstrumentationRegistry.getTargetContext(), ViewBoxActivity.class);
            final Bundle bundleWrap = new Bundle();
            bundleWrap.putParcelable(ViewBoxActivity.EXTRA_KEY_VIEW_BOX_REMOTE_CONTROLLER, Parcels.wrap(mockedViewBoxApplication));
            intent.putExtra(ViewBoxActivity.EXTRA_KEY_BUNDLED_VIEW_BOX_REMOTE_CONTROLLER, bundleWrap);

            return intent;
        }

        @Override
        protected void afterActivityLaunched() {
            super.afterActivityLaunched();
            mockedViewBoxRemoteController = activityRule.getActivity().getViewBoxRemoteController();
        }
    };

    @Test
    public void givenTheLampIsOffWhenSwitchingTheLeftLampThenItShouldDisplayOn() throws Exception {
        onView(withId(R.id.ivLeftLamp)).perform(click());
        onView(withId(R.id.component_controller)).check(matches(isDisplayed()));
        onView(withId(R.id.switchLight)).check(matches(isNotChecked()))
                .perform(click()).check(matches(isChecked()));

        verify(mockedViewBoxRemoteController).toggleLed();
    }

    @Test
    public void disconnectTheViewBoxInOnPause() throws Exception {
        activityRule.getActivity().finish();
        verify(mockedViewBoxRemoteController).disconnect();
    }
}