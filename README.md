# WiFiCinstaller - WiFi Profile Manager
A lightweight Windows utility written in C that helps manage multiple WiFi profiles with the same SSID (Access Point name) but different passwords by allowing you to store them as separate profiles.

![Application Icon](assets/logo.png)   

## Features  
- Batch install all stored WiFi profiles with a single click
- Simple GUI interface for easy operation
- Designed to work with profiles sharing the same SSID but having different passwords

## Prerequisites 
- Windows operating system
- MinGW compiler (for building from source)
- Administrator privileges (required for WiFi profile installation)

## Usage  
1. **Export your current WiFi profile**:
   ```
   netsh wlan export profile name="Example-WiFi"
   ```
2. **Modify the exported XML files**:
   - Rename the files to distinguish between different profiles (e.g., "Home-WiFi.xml", "Office-WiFi.xml")
   - Place all modified profiles in the `profiles` folder next to the executable
3. **Run the program**:
   - Execute `program.exe` as Administrator
   - Click the main button to install all profiles from the `profiles` folder

## Building from Source
1. Place these files in the same directory:
   - `main.c` (main program file)
   - `resource.rc` (resource script in the `assets` folder)
   - `icon.ico` (in the `assets` folder)
2. Compile with MinGW using these commands:
   ```
   windres resource.rc -O coff -o resource.res
   gcc main.c resource.res -o program.exe -mwindows
   ```

## Notes
- Always run the program as Administrator to allow WiFi profile installation
- The program will process all `.xml` files in the `profiles` folder
- Original WiFi profiles are not modified - new ones are added alongside them 

## License  
Released under the [MIT License](LICENSE).  

---  
*Note: This tool modifies system network settings. Use with caution.*