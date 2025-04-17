package me.longluo.gstreamer

import android.os.Bundle
import android.view.View
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import org.freedesktop.gstreamer.GStreamer


class MainActivity : AppCompatActivity() {

    private external fun nativeGetGStreamerInfo(): String

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        try {
            GStreamer.init(this)
        } catch (e: Exception) {
            e.printStackTrace()
            Toast.makeText(this, e.message, Toast.LENGTH_LONG).show()
            finish()
            return
        }

        setContentView(R.layout.activity_main)
        val tv = findViewById<View>(R.id.tv_version) as TextView
        tv.text = "Welcome to ${nativeGetGStreamerInfo()}!"
    }

    companion object {
        init {
            System.loadLibrary("gstreamer_android")
            System.loadLibrary("gstreamer_android_tutorial_1")
        }
    }
}
