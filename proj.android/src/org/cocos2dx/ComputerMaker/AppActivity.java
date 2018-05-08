/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.ComputerMaker;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.Activity;
import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.os.Bundle;
import android.os.Vibrator;
import android.util.Log;
import android.view.WindowManager;

public class AppActivity extends Cocos2dxActivity implements SensorEventListener {
	public static Vibrator vibe;
	private static Activity self;
	private static AppActivity _appActivity;
	private static SensorManager mSensorManager;
	private static Sensor mSensorAccelerometer;
	private static Sensor mSensorMagnetometer;
	public static float f_device_x_rotation = 0;
	public static float f_device_y_rotation = 0;
	public static AudioRecord audio_record = null;
	public static int audio_min_size ;
	public static float mic_level = 0;
	public static float f_device_accel = 0;
	
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		self = this;
		 _appActivity = this;
		vibe = (Vibrator) getSystemService(Context.VIBRATOR_SERVICE);	
		 

	     audio_min_size= AudioRecord.getMinBufferSize(8000, AudioFormat.CHANNEL_IN_MONO, AudioFormat.ENCODING_PCM_16BIT);
		  audio_record = new AudioRecord(MediaRecorder.AudioSource.MIC, 8000,AudioFormat.CHANNEL_IN_MONO, AudioFormat.ENCODING_PCM_16BIT,audio_min_size);
		  mic_level = 0;
	}
	
	 @Override
	   protected void onPause()
	   {
	    	super.onPause();
	    }
	    @Override
	    protected void onResume()
	    {
	    	super.onResume();
	    }
	public static String changeStringToUTF8(byte[] arr) throws Exception
	{
		//CharBuffer cbuffer = CharBuffer.wrap((new String(str.getBytes(), "EUC-KR")).toCharArray());
		//Charset utf8charset = Charset.forName("UTF-8");
		//ByteBuffer bbuffer = utf8charset.encode(cbuffer);

		//encoded UTF-8 string
		//String tmpDecode = new String(bbuffer.array());
		//return tmpDecode;
		String ansi = new String(arr, "EUC-KR");
		byte[] utf = ansi.getBytes("UTF-8");
		String ret = new String(utf, "UTF-8");		
		return ret;
	}
	public static void startCleanSetting()
	{
		mSensorManager = (SensorManager)_appActivity.getSystemService(Context.SENSOR_SERVICE);
	     mSensorAccelerometer = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
	     mSensorMagnetometer = mSensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);
	     mSensorManager.registerListener(_appActivity, mSensorAccelerometer, SensorManager.SENSOR_DELAY_GAME);
	     mSensorManager.registerListener(_appActivity, mSensorMagnetometer, SensorManager.SENSOR_DELAY_GAME);
		 
		 audio_record.startRecording();
		 
	}
	public static void endCleanSetting()
	{
		mSensorManager.unregisterListener(_appActivity, mSensorAccelerometer);
		mSensorManager.unregisterListener(_appActivity, mSensorMagnetometer);
		
		if (audio_record != null) {
	    	audio_record.stop();
	     }
	}
	public static void vibe()
	{
		
		 self.runOnUiThread(new Runnable(){
	            
	            @Override
	            public void run() {
	                // TODO Auto-generated method stub
	            	
	        		vibe.vibrate(100);
	            }
	            
	            
	        });
	}
	public static float getMicLevel() {
		//Calculate is too slow so run on thread
		
		self.runOnUiThread(new Runnable(){
			@Override
			public void run() {
				 short[] buffer = new short[audio_min_size];
				    audio_record.read(buffer, 0, audio_min_size);
				    int max = 0;
				    for (short s : buffer)
				    {
				        if (Math.abs(s) > max)
				        {
				            max = Math.abs(s);
				        }
			     }
			     mic_level = max;
			}
		});
	   return mic_level;
	}
	public static float getDeviceXRotation()
	{
		return f_device_x_rotation;
	}
	public static float getDeviceYRotation()
	{
		return f_device_y_rotation;
	}
	public static float getDeviceAccel()
	{
		return f_device_accel;
	}

	 public void onAccuracyChanged(Sensor sensor, int accuracy) {  }
	 
	  float[] mGravity;
	  float[] mGeomagnetic;
	  public void onSensorChanged(SensorEvent event) {
	    if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER)
	    {
	    	float[] gravity_data = new float[3];
	    	float[] accel_data = new float[3];
	    	float[] m_acc_data = new float[3];
	    	final float alpha = (float)0.8;
	     
	    	gravity_data[0] = alpha * gravity_data[0] + (1 - alpha) * event.values[0]; //먼저 중력데이터를 계산함
			gravity_data[1] = alpha * gravity_data[1] + (1 - alpha) * event.values[1];
			gravity_data[2] = alpha * gravity_data[2] + (1 - alpha) * event.values[2];
			accel_data[0] = event.values[0] - gravity_data[0]; // 순수 가속도센서값에 중력값을 빼줌
			accel_data[1] = event.values[1] - gravity_data[1]; // 아니면 약 9.81 어쩌고 하는값이 더해짐
			accel_data[2] = event.values[2] - gravity_data[2];
			
			f_device_accel = accel_data[1];
			//Log.e("accel", String.valueOf(f_device_accel));
	    	mGravity = event.values;
	    }
	    if (event.sensor.getType() == Sensor.TYPE_MAGNETIC_FIELD)
	      mGeomagnetic = event.values;
	    if (mGravity != null && mGeomagnetic != null) {
	      float R[] = new float[9];
	      float I[] = new float[9];
	      boolean success = SensorManager.getRotationMatrix(R, I, mGravity, mGeomagnetic);
	      if (success) {
	        float orientation[] = new float[3];
	        SensorManager.getOrientation(R, orientation);	        
	        f_device_x_rotation = orientation[1]; // orientation contains: azimut, pitch and roll
	        f_device_x_rotation = -(float) Math.toDegrees(f_device_x_rotation);
	        
	        f_device_y_rotation = orientation[2]; // orientation contains: azimut, pitch and roll
	        f_device_y_rotation = (float) Math.toDegrees(f_device_y_rotation);
	        
	      }
	    }
	  }
}
