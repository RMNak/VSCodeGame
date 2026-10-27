package com.rmnaik.testandriod;

import static android.webkit.WebView.setWebContentsDebuggingEnabled;

import android.annotation.SuppressLint;
import android.content.Context;
import android.net.Uri;
import android.os.Bundle;
import android.webkit.JavascriptInterface;
import android.webkit.WebChromeClient;
import android.webkit.WebResourceRequest;
import android.webkit.WebResourceResponse;
import android.webkit.WebView;
import android.webkit.WebViewClient;

import androidx.activity.EdgeToEdge;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;
import androidx.webkit.WebViewAssetLoader;

public class MainActivity extends AppCompatActivity {

    @SuppressLint("SetJavaScriptEnabled")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);

        WebView mywebView = findViewById(R.id.myWebView);

        //Do configuration settings

        mywebView.getSettings().setJavaScriptEnabled(true);
        mywebView.setWebChromeClient(new WebChromeClient());

        mywebView.addJavascriptInterface(new WebInterface(this), "Andriod");

        setWebContentsDebuggingEnabled(false);

        final WebViewAssetLoader assetLoader = new WebViewAssetLoader.Builder()
                .addPathHandler("/assets/", new WebViewAssetLoader.AssetsPathHandler(this))
                .addPathHandler("/res/", new WebViewAssetLoader.AssetsPathHandler(this)).build();

        mywebView.setWebViewClient(new localContentWebViewClient(assetLoader));

        //mywebView.loadUrl("http://appassets.androidplatform.net//assets//www//index.html");


        mywebView.loadUrl("file:///android_asset/www/index.html");
    }

    public static class localContentWebViewClient extends WebViewClient {
        private final WebViewAssetLoader myAssetLoader;

        public localContentWebViewClient(WebViewAssetLoader myAssetLoader) {
            this.myAssetLoader = myAssetLoader;
        }

        @Override
        @RequiresApi(21)
        public WebResourceResponse shouldInterceptRequest(WebView view, WebResourceRequest request)
        {
           return  myAssetLoader.shouldInterceptRequest(request.getUrl());
        }

        @Override
        public WebResourceResponse shouldInterceptRequest(WebView view, String Url)
        {
            return  myAssetLoader.shouldInterceptRequest(Uri.parse((Url)));
        }

        @Override
        public  boolean shouldOverrideUrlLoading(WebView view, String Url)
        {
            if (Url.contains("@"))
            {
                return  true;
            }

            return false;
        }
    }

    public class WebInterface
    {
        Context myContext;

        WebInterface(Context _context)
        {
            myContext = _context;
        }
        @JavascriptInterface
        public  String SocialMediaLink()
        {
            return "https://www.youtube.com/watch?v=_aOpiRiaUak@YouTube;" +
                    "https://www.youtube.com/watch?v=_aOpiRiaUak@FaceBook;" +
                    "https://developer.android.com/develop/ui/views/layout/webapps/webview#kotlin@Developer";
        }
    }
}