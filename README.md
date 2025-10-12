
EtwEnumerator.Win32Metadata
===========================

This project contains code to build and publish [the EtwEnumerator.Win32Metadata nuget package](https://www.nuget.org/packages/EtwEnumerator.Win32Metadata). The package wraps the **EtwEnumerator library** from [the ETW repository](https://github.com/microsoft/ETW) into a winmd (Windows metadata) file. If you combine it with [Microsoft.Windows.CsWin32](https://www.nuget.org/packages/Microsoft.Windows.CsWin32), it will allow you to generate signatures (PInvokes) to easily use EtwEnumerator object in your executable/library.

Who is it for
-------------

You may profit from this package if you plan to implement the [PEVENT_RECORD_CALLBACK](https://learn.microsoft.com/en-us/windows/win32/api/evntrace/nc-evntrace-pevent_record_callback) in C# and want to parse ETW events.

How to use it
-------------

1. Install the required Nuget packages:

- [Microsoft.Windows.CsWin32](https://www.nuget.org/packages/Microsoft.Windows.CsWin32)
- [EtwEnumerator.Win32Metadata](https://www.nuget.org/packages/EtwEnumerator.Win32Metadata)

2. Create a NativeMethods.txt file in the root folder of your project and list native functions and structures (including the one from EtwEnumerator) you plan to use, for example:

```
// --- EtwEnumerator ---
CreateEtwEnumerator
DeleteEtwEnumerator

// --- cswin32 ---
CreateFile
ControlTrace
EnableTraceEx2
```

Please also check the [cswin32 project README file](https://github.com/microsoft/CsWin32/blob/main/README.md) for other configuration options of the PInvoke generators.

3. You are ready to use the native functions in your code :)

My other project, [wtrace](https://github.com/lowleveldesign/wtrace), uses this package to parse ETW events.
