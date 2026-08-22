# SuiteUTFWorkbench

SuiteUTFWorkbench is a Windows desktop application for inspecting, diagnosing,
normalising, and converting UTF-encoded content.

## Prerequisites

- Visual Studio with the **Desktop development with C++** workload
- A Windows 10 or later SDK

## Clone and build

Clone the repository and initialise its pinned SuiteUTF dependency:

```powershell
git clone --recurse-submodules https://github.com/Icabod66/SuiteUTFWorkbench.git
```

Open `SuiteUTFWorkbench.sln` in Visual Studio. The solution supports Debug,
Development, and Release configurations for Win32 and x64. Building the
SuiteUTFWorkbench project also builds and links the SuiteUTF static library.

For an existing clone, initialise the dependency with:

```powershell
git submodule update --init --recursive
```
