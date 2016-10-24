package com.example.ren.expressassistant;


import android.graphics.Bitmap;
import android.graphics.Bitmap.Config;
import android.graphics.drawable.BitmapDrawable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.ImageView;
import android.view.View;
import android.graphics.BitmapFactory;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {


    private static String TAG = "OpenCVLoader";
    private ImageView show_image;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();

    }

    private void initView() {
        TextView textView = (TextView)findViewById(R.id.sample_text);
        textView.setText(NDKloader.stringFromJNI());
        show_image = (ImageView) findViewById(R.id.show_image);
        show_image.setImageResource(R.drawable.testpic);
        findViewById(R.id.pic).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //恢复
                backPic();
            }
        });
        findViewById(R.id.gray_pic).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //变灰
                grayPic();
            }
        });
    }
    private void backPic(){
        show_image.setImageResource(R.drawable.testpic);
    }
    private void grayPic(){
        Bitmap bmp = BitmapFactory.decodeResource(getResources(),R.drawable.testpic);
        int w = bmp.getWidth();
        int h = bmp.getHeight();
        int[] pixels = new int[w*h];
        bmp.getPixels(pixels, 0, w, 0, 0, w, h);
        //recall JNI
        int[] resultInt = NDKloader.getGrayImage(pixels, w, h);
        //int[] resultInt = NDKloader.Cvtest(pixels,w,h);
        Bitmap resultImg = Bitmap.createBitmap(w, h, Bitmap.Config.RGB_565);

        resultImg.setPixels(resultInt, 0, w, 0, 0, w, h);
        show_image.setImageBitmap(resultImg);
    }



}
