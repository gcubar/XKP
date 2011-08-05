@echo off
rem set JAVA_HOME = c:\Progra~1\Java\jdk1.6.0_22\
rem set in Path = android-sdk-windows\tools; android-sdk-windows\platforms-tools;
rem set the base directory of android

    aapt p -m -J D:\xkp\xss\production\android\Contacts\src -M AndroidManifest.xml -S D:\xkp\xss\production\android\Contacts\res -I d:/android/android-sdk-windows/platforms/android-8/android.jar
    javac -encoding ascii -target 1.5 -d D:\xkp\xss\production\android\Contacts\bin -bootclasspath d:/android/android-sdk-windows/platforms/android-8/android.jar D:\xkp\xss\production\android\Contacts\src/com/xkp/android/Contacts/*.java
    dx --dex --output=D:\xkp\xss\production\android\Contacts\bin/classes.dex D:\xkp\xss\production\android\Contacts\bin
    aapt p -f -M AndroidManifest.xml -S D:\xkp\xss\production\android\Contacts\res -I d:/android/android-sdk-windows/platforms/android-8/android.jar -F D:\xkp\xss\production\android\Contacts\bin/output.ap_ 
    apkbuilder D:\xkp\xss\production\android\Contacts\bin/Contacts.apk -z D:\xkp\xss\production\android\Contacts\bin/output.ap_ -f D:\xkp\xss\production\android\Contacts\bin/classes.dex -rf D:\xkp\xss\production\android\Contacts\src -rj D:\xkp\xss\production\android\Contacts\libs
    adb install -r D:\xkp\xss\production\android\Contacts\bin/Contacts.apk

