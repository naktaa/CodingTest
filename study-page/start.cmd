@echo off
setlocal
cd /d "%~dp0"

where node >nul 2>&1
if errorlevel 1 goto missing_node
where npm.cmd >nul 2>&1
if errorlevel 1 goto missing_node

node -e "const [major, minor] = process.versions.node.split('.').map(Number); process.exit(major > 22 || (major === 22 && minor >= 12) ? 0 : 1)"
if errorlevel 1 goto old_node

if not exist "node_modules\vite\bin\vite.js" goto install
if not exist "node_modules\.bin\vite.cmd" goto install
node -e "require('rollup')" >nul 2>&1
if errorlevel 1 goto install
goto run

:install
echo Installing project dependencies for Windows...
call npm.cmd install
if errorlevel 1 goto failed

:run
echo Keep this window open while using the study page.
call npm.cmd run dev -- --open
if errorlevel 1 goto failed
exit /b 0

:missing_node
echo Node.js and npm were not found. Install Node.js 22.12 or newer.
echo Then restart VS Code and run this file again.
pause
exit /b 1

:old_node
echo Node.js 22.12 or newer is required. Current version:
node --version
pause
exit /b 1

:failed
echo The command failed. See the error above.
pause
exit /b 1
