cd ~/imgui-app
cat > app/src/main/java/com/neon/panel/MainActivity.java <<'EOF'
package com.neon.panel;

import android.app.Activity;
import android.os.Bundle;
import android.content.Intent;
import android.widget.Button;
import android.widget.FrameLayout;
import android.view.Gravity;
import android.view.ViewGroup;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MainActivity extends Activity {

    private PanelView panelView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        FrameLayout layout = new FrameLayout(this);

        panelView = new PanelView();
        layout.addView(panelView);

        Button launchButton = new Button(this);
        launchButton.setText("ЗАПУСТИТЬ ИГРУ");
        launchButton.setOnClickListener(v -> launchGame());

        FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(
            ViewGroup.LayoutParams.WRAP_CONTENT,
            ViewGroup.LayoutParams.WRAP_CONTENT,
            Gravity.TOP | Gravity.CENTER_HORIZONTAL
        );
        params.topMargin = 20;

        layout.addView(launchButton, params);
        setContentView(layout);
    }

    private void launchGame() {
        try {
            Intent intent = getPackageManager()
                .getLaunchIntentForPackage("com.standrise.game");

            if (intent != null) {
                startActivity(intent);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        panelView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        panelView.onResume();
    }

    private class PanelView extends GLSurfaceView {

        PanelView() {
            super(MainActivity.this);
            setEGLContextClientVersion(3);
            setRenderer(new PanelRenderer());
            setRenderMode(RENDERMODE_CONTINUOUSLY);
        }

        @Override
        public boolean onTouchEvent(MotionEvent event) {
            nativeTouch(
                event.getX(),
                event.getY(),
                event.getActionMasked()
            );
            return true;
        }
    }

    private static class PanelRenderer implements GLSurfaceView.Renderer {

        @Override
        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            nativeInit();
        }

        @Override
        public void onSurfaceChanged(GL10 gl, int width, int height) {
            nativeResize(width, height);
        }

        @Override
        public void onDrawFrame(GL10 gl) {
            nativeRender();
        }
    }

    private static native void nativeInit();
    private static native void nativeResize(int width, int height);
    private static native void nativeRender();
    private static native void nativeTouch(float x, float y, int action);

    static {
        System.loadLibrary("neonpanel");
    }
}
EOF