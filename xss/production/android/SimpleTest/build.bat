@echo off
rem set JAVA_HOME = c:\Progra~1\Java\jdk1.6.0_22\
rem set in Path = android-sdk-windows\tools; android-sdk-windows\platforms-tools;
rem set the base directory of android

    aapt p -m -J d:\xkp\xss\production\android\SimpleTest\src -M AndroidManifest.xml -S d:\xkp\xss\production\android\SimpleTest\res -I d:/android/android-sdk-windows/platforms/android-8/android.jar
    javac -encoding ascii -target 1.5 -d d:\xkp\xss\production\android\SimpleTest\bin -bootclasspath d:/android/android-sdk-windows/platforms/android-8/android.jar d:\xkp\xss\production\android\SimpleTest\src/com/xkp/android/SimpleTest/*.java
    dx --dex --output=d:\xkp\xss\production\android\SimpleTest\bin/classes.dex d:\xkp\xss\production\android\SimpleTest\bin
    aapt p -f -M AndroidManifest.xml -S d:\xkp\xss\production\android\SimpleTest\res -I d:/android/android-sdk-windows/platforms/android-8/android.jar -F d:\xkp\xss\production\android\SimpleTest\bin/output.ap_ 
    apkbuilder d:\xkp\xss\production\android\SimpleTest\bin/SimpleTest.apk -z d:\xkp\xss\production\android\SimpleTest\bin/output.ap_ -f d:\xkp\xss\production\android\SimpleTest\bin/classes.dex -rf d:\xkp\xss\production\android\SimpleTest\src -rj d:\xkp\xss\production\android\SimpleTest\libs
    adb install -r d:\xkp\xss\production\android\SimpleTest\bin/SimpleTest.apk

