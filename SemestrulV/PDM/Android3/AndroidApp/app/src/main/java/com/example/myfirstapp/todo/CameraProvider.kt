package com.example.myfirstapp.todo

import android.Manifest
import android.annotation.SuppressLint
import android.content.Context
import android.content.pm.PackageManager
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.graphics.ImageDecoder
import android.widget.Toast
import androidx.activity.compose.rememberLauncherForActivityResult
import androidx.activity.result.contract.ActivityResultContracts
import androidx.compose.animation.AnimatedVisibility
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.size
import androidx.compose.material3.Button
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.unit.dp
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import androidx.core.content.FileProvider
import coil.compose.AsyncImage
import com.example.myfirstapp.BuildConfig
import java.io.ByteArrayOutputStream
import java.io.File
import java.text.SimpleDateFormat
import java.util.Base64
import java.util.Date
import java.util.Objects

const val CAMERA_PERMISSION_REQUEST_CODE = 1001

@Composable
fun ImagePicker(originalUri: String, uriChanged: (String) -> Unit) {
    val context = LocalContext.current
    var currentPhotoUrl by remember { mutableStateOf(value = originalUri) }

    val file = context.createImageFile()
    val uri = FileProvider.getUriForFile(
        Objects.requireNonNull(context),
        BuildConfig.APPLICATION_ID + ".provider", file
    )

    val cameraLauncher = rememberLauncherForActivityResult(
        contract = ActivityResultContracts.TakePicture(),
        onResult = { success ->
            if (success) {
                val bmp = ImageDecoder.decodeBitmap(ImageDecoder.createSource(context.contentResolver, uri))
                val scaled = Bitmap.createScaledBitmap(bmp, 128, 128, false)

                val byteArrayOutputStream = ByteArrayOutputStream()
                scaled.compress(Bitmap.CompressFormat.JPEG, 100, byteArrayOutputStream)
                val byteArray: ByteArray = byteArrayOutputStream.toByteArray()
                val encoded: String = "data:image/jpg;base64," + Base64.getEncoder().encodeToString(byteArray)

                currentPhotoUrl = encoded
                uriChanged(currentPhotoUrl)
            }
        }
    )

    fun toBitmap(url64: String): Bitmap {
        val data64 = url64.substring("data:image/jpg;base64,".length)
        val bytes = Base64.getDecoder().decode(data64)
        val bmp = BitmapFactory.decodeByteArray(bytes, 0, bytes.size)
        return bmp.copy(Bitmap.Config.ARGB_8888, true)
    }

    Column(
        modifier = Modifier.fillMaxSize(),
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        AnimatedVisibility(visible = currentPhotoUrl.isNotEmpty()) {
            AsyncImage(
                modifier = Modifier.size(size = 240.dp),
                model = toBitmap(currentPhotoUrl),
                contentDescription = null
            )
        }
        Button(onClick = {
            if (context.checkAndRequestCameraPermission()) {
                cameraLauncher.launch(uri)
            }
        }) {
            Text(text = "Take a photo with Camera")
        }
    }
}

@SuppressLint("SimpleDateFormat")
fun Context.createImageFile(): File {
    val timeStamp = SimpleDateFormat("yyyyMMdd_HHmmss").format(Date())
    val imageFileName = "JPEG_" + timeStamp + "_"
    return File.createTempFile(
        imageFileName, /* prefix */
        ".jpg", /* suffix */
        externalCacheDir /* directory */
    )
}

fun Context.checkAndRequestCameraPermission(): Boolean {
    val permission = Manifest.permission.CAMERA
    return if (ContextCompat.checkSelfPermission(this, permission) == PackageManager.PERMISSION_GRANTED) {
        true
    } else {
        ActivityCompat.requestPermissions(
            this as android.app.Activity,
            arrayOf(permission),
            CAMERA_PERMISSION_REQUEST_CODE
        )
        false
    }
}
