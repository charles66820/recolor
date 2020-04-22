package fr.toutdoux.recolor;

import org.libsdl.app.SDLActivity;

import android.app.Activity;
import android.content.*;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.*;
import android.widget.CompoundButton;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Switch;
import android.widget.TextView;

public class RecolorActivity extends Activity {
    private static final String TAG = "RECOLOR";

    public static final String EXTRA_MESSAGE = "fr.toutdoux.recolor.MESSAGE";

    private Uri fileUri;
    private String filePath;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        // render main activity
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_recolor);
    }

    public void startLoadGame(View view) {
        // Create an Intent with a new activity
        Intent intent = new Intent(this, SDLActivity.class);
        intent.putExtra(EXTRA_MESSAGE, filePath); // send msg to activity
        startActivity(intent);
    }

    public void startRandGame(View view) {
        String message = null;

        // Create args string
        String width = ((EditText) findViewById(R.id.editTextArgWidth)).getText().toString();
        String height = ((EditText) findViewById(R.id.editTextArgHeight)).getText().toString();
        String nbMaxMove = ((EditText) findViewById(R.id.editTextArgNbMaxMove)).getText().toString();
        String nbMaxColor = ((EditText) findViewById(R.id.editTextArgNbMaxColor)).getText().toString();
        String switchIsWrapping = (((Switch) findViewById(R.id.switchIsWrapping)).isChecked()) ? "S" : "N";

        message = width + " " + height + " " + nbMaxMove + " " + (nbMaxColor.isEmpty() ? switchIsWrapping :
            nbMaxColor + " " + switchIsWrapping);

        // Create an Intent with a new activity
        Intent intent = new Intent(this, SDLActivity.class);
        intent.putExtra(EXTRA_MESSAGE, message); // send msg to activity
        startActivity(intent);
    }

    public void chooseFile(View view) {
        Intent chooseFile = new Intent(Intent.ACTION_GET_CONTENT);
        chooseFile.setType("*/*");
        chooseFile = Intent.createChooser(chooseFile, "Choisissez un fichier");
        startActivityForResult(chooseFile, 1);
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        switch (requestCode) {
            case 1:
                if (resultCode == -1) {
                    fileUri = data.getData();
                    assert fileUri != null;
                    filePath = fileUri.getPath().split(":")[1];
                    TextView filePathElm = (TextView) findViewById(R.id.file_path);
                    filePathElm.setText(filePath);
                    filePathElm.setVisibility(View.VISIBLE);
                }

                break;
        }
    }
}
