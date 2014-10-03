adb shell am force-stop com.PixlGames.SuperPlay.BLT
adb logcat -c
adb shell am start -n com.PixlGames.SuperPlay.BLT/android.app.NativeActivity
adb logcat SuperPlay-Log:V *:S
