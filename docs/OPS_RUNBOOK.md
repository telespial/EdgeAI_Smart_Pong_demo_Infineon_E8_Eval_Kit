# OPS_RUNBOOK

## Environment
Use these env vars for reproducible CLI builds:

```bash
export CY_TOOLS_PATHS=/home/user/toolchains/infineon/ModusToolbox_local/opt/Tools/ModusToolbox/tools_3.7
export CY_COMPILER_GCC_ARM_DIR=/home/user/toolchains/infineon/ModusToolbox_local/opt/Tools/mtb-gcc-arm-eabi/14.2.1/gcc
export CY_TOOL_edgeprotecttools_EXE_ABS=/home/user/toolchains/infineon/ModusToolbox_local/opt/Tools/ModusToolbox-Edge-Protect-Security-Suite-1.6.1/tools/edgeprotecttools/bin/edgeprotecttools
```

## Clean Build
```bash
make clean TOOLCHAIN=GCC_ARM
make build TOOLCHAIN=GCC_ARM
```

## Program Kit
```bash
make program TOOLCHAIN=GCC_ARM
```

## Toggle Smart Pong Prep Screen
Edit `proj_cm55/Makefile`:
```make
# DEFINES+=APP_SMART_PONG_MODE=1
```
Uncomment for Smart Pong prep screen, then build/program.

## Verify Device Detection
During flash logs, confirm:
- device family `PSE84xGxS2`
- detected part like `PSE846GPS2...`
- `Boot Status : CYBOOT_SUCCESS`

## Troubleshooting
- If build cannot find tools, re-export env vars above.
- If flash works but no display, validate hardware jumpers and `CONFIG_DISPLAY`.
