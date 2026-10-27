package com.rmnaik.testcardgame;

import android.annotation.SuppressLint;
import android.content.Context;
import android.net.Uri;
import android.os.Bundle;
import android.webkit.JavascriptInterface;
import android.webkit.WebChromeClient;
import android.webkit.WebResourceResponse;
import android.webkit.WebView;

import androidx.activity.EdgeToEdge;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;
import androidx.webkit.WebViewAssetLoader;
import androidx.webkit.WebViewClientCompat;

public class MainActivity extends AppCompatActivity {

    @SuppressLint({"JavascriptInterface", "SetJavaScriptEnabled"})
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        WebView myWebView = findViewById(R.id.MREGame);
        myWebView.getSettings().setJavaScriptEnabled(true);
        myWebView.setWebChromeClient(new WebChromeClient());
        myWebView.addJavascriptInterface(new WebInterFace(this),  "Android");

        WebView.setWebContentsDebuggingEnabled(false);
        final WebViewAssetLoader assetLoader = new WebViewAssetLoader.Builder()
                .addPathHandler("/assets/", new WebViewAssetLoader.AssetsPathHandler(this))
                .addPathHandler("/res/", new WebViewAssetLoader.AssetsPathHandler(this))
                .build();

        myWebView.setWebViewClient(new localContentWebViewClient(assetLoader));
    }
private static class localContentWebViewClient extends WebViewClientCompat{
        private final WebViewAssetLoader myAssetLoader;

        localContentWebViewClient( WebViewAssetLoader _assetLoader)
        {
            myAssetLoader = _assetLoader;
        }

        @Override
        @RequiresApi(21)
        public WebResourceResponse shouldInterceptRequest(WebView view, String url)
        {
            return myAssetLoader.shouldInterceptRequest((Uri.parse(url)));
        }

        @Override
    public boolean shouldOverrideUrlLoading(WebView view, String url){
            if(url.contains("naik")){
                return true;
            }


            return false;
        }
}

    public static class WebInterFace
    {
        Context mainContext;

        WebInterFace(Context _context)
        {
            mainContext = _context;
        }

        @JavascriptInterface
        public String SocialMediaLinks()
        {
            return "https://facebook/@coding&facebook;" +
                    "https://youtube.com/@youtub&coding;" +
                    "https://twitter.com/twitter;";
        }
    }
}