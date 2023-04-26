This is my attempt to create a unit test template file for the GD32F330c-start and GD32F350g-start board and also a native option.

I started following the procedures from this tutorial: https://piolabs.com/blog/insights/unit-testing-part-1.html

I was able to get it to run properly.  I then tried to incorporate the gd32F3x0 spl framework using the directions from this page https://docs.platformio.org/en/latest/tutorials/ststm32/stm32cube_debugging_unit_testing.html#tutorial-stm32cube-debugging-unit-testing

However, I am not able to compile and I get the following errors: 
Processing test_common in gd32350g_start environment
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Building & Uploading...
Library Manager: Installing throwtheswitch/Unity @ ^2.5.2
Unpacking  [####################################]  100%
Library Manager: Unity@2.5.2 has been installed!
UnitTestSuiteError: Could not find Unity configuration for the `spl` framework.
Learn how to create a custom Unity configuration athttps://docs.platformio.org/en/latest/advanced/unit-testing/frameworks/unity.html:
  File "C:\Users\kwong\.platformio\penv\lib\site-packages\platformio\builder\main.py", line 187:
    env.SConscript("$BUILD_SCRIPT")
  File "C:\Users\kwong\.platformio\packages\tool-scons\scons-local-4.4.0\SCons\Script\SConscript.py", line 597:
    return _SConscript(self.fs, *files, **subst_kw)
  File "C:\Users\kwong\.platformio\packages\tool-scons\scons-local-4.4.0\SCons\Script\SConscript.py", line 285:
    exec(compile(scriptdata, scriptname, 'exec'), call_stack[-1].globals)
  File "C:\Users\kwong\.platformio\platforms\gd32\builder\main.py", line 128:
    target_elf = env.BuildProgram()
  File "C:\Users\kwong\.platformio\packages\tool-scons\scons-local-4.4.0\SCons\Util.py", line 737:
    return self.method(*nargs, **kwargs)
  File "C:\Users\kwong\.platformio\penv\lib\site-packages\platformio\builder\tools\piobuild.py", line 61:
    env.ProcessProjectDeps()
  File "C:\Users\kwong\.platformio\packages\tool-scons\scons-local-4.4.0\SCons\Util.py", line 737:
    return self.method(*nargs, **kwargs)
  File "C:\Users\kwong\.platformio\penv\lib\site-packages\platformio\builder\tools\piobuild.py", line 137:
    plb = env.ConfigureProjectLibBuilder()
  File "C:\Users\kwong\.platformio\packages\tool-scons\scons-local-4.4.0\SCons\Util.py", line 737:
    return self.method(*nargs, **kwargs)
  File "C:\Users\kwong\.platformio\penv\lib\site-packages\platformio\builder\tools\piolib.py", line 1166:
    project.env.ConfigureTestTarget()
  File "C:\Users\kwong\.platformio\packages\tool-scons\scons-local-4.4.0\SCons\Util.py", line 737:
    return self.method(*nargs, **kwargs)
  File "C:\Users\kwong\.platformio\penv\lib\site-packages\platformio\builder\tools\piotest.py", line 53:
    test_runner.configure_build_env(env)
  File "C:\Users\kwong\.platformio\penv\lib\site-packages\platformio\test\runners\unity.py", line 225:
    self.generate_unity_extras(env.subst("$UNITY_CONFIG_DIR"))
  File "C:\Users\kwong\.platformio\penv\lib\site-packages\platformio\test\runners\unity.py", line 255:
    framework_config = self.get_unity_framework_config()
  File "C:\Users\kwong\.platformio\penv\lib\site-packages\platformio\test\runners\unity.py", line 209:
    raise UnitTestSuiteError(
Uploading stage has failed, see errors above. Use `pio test -vvv` option to enable verbose output.
------------------------------------------------------------------------------------------------------ gd32350g_start:test_common [ERRORED] Took 4.90 seconds ------------------------------------------------------------------------------------------------------

Processing test_embedded in gd32350g_start environment
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Building & Uploading...
test\test_embedded\unity_config.c: In function 'unityOutputStart':
test\test_embedded\unity_config.c:37:34: error: 'UART_TX_AF' undeclared (first use in this function)
   37 |     gpio_af_set(UART_TX_RX_GPIO, UART_TX_AF, UART_TX_GPIO_PIN);
      |                                  ^~~~~~~~~~
test\test_embedded\unity_config.c:37:34: note: each undeclared identifier is reported only once for each function it appears in
test\test_embedded\unity_config.c:38:34: error: 'UART_RX_AF' undeclared (first use in this function)
   38 |     gpio_af_set(UART_TX_RX_GPIO, UART_RX_AF, UART_RX_GPIO_PIN);
      |                                  ^~~~~~~~~~
*** [.pio\build\gd32350g_start\test\test_embedded\unity_config.o] Error 1
Uploading stage has failed, see errors above. Use `pio test -vvv` option to enable verbose output.
----------------------------------------------------------------------------------------------------- gd32350g_start:test_embedded [ERRORED] Took 4.31 seconds -----------------------------------------------------------------------------------------------------

============================================================================================================================= SUMMARY ============================================================================================================================= 
Environment     Test           Status    Duration
--------------  -------------  --------  ------------
gd32350g_start  test_common    ERRORED   00:00:04.903
gd32350g_start  test_embedded  ERRORED   00:00:04.305
============================================================================================================ 2 test cases: 0 succeeded in 00:00:09.209 ============================================================================================================ 

 *  The terminal process "C:\Users\kwong\.platformio\penv\Scripts\platformio.exe 'test', '--environment', 'gd32350g_start'" terminated with exit code: 1. 
 *  Terminal will be reused by tasks, press any key to close it. 
