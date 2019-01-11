# mmInTouchSFL
A script function library for InTouch

### Functions: 
int ReadWindowLocation(string ApplicationDirectory, string WindowName, string XTag, string YTag)

Reads the design time window offset from the appropriate .win file in the given application directory and writes it to the tags XTag, YTag.  This can be used to show a window at some location offset from the designed location, eg on a different monitor, without having to hardcode coordinates.

Return codes
 * 0 - Success (however if tags provided are invalid, they will not be written to)
 * 1 - Error: Could not read window list from application directory
 * 2 - Error: Window index could not be located in list file
 * 3 - Error: Could not open window file
 * 4 - Error: Could not read window data    
 * 5 - Error: InTouch is not running (could not access PtAcc)

Example usage:
```
DIM result as INTEGER;
 
result = ReadWindowLocation(InfoInTouchAppDir(), "MyWindow", XTag.Name, YTag.Name);
```
