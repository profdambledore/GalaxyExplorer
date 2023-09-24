# Galaxy Explorer

Galaxy Explorer is a challenge that I set for myself to re-create Star Citizen's Ship system in Unreal Engine 4.  This includes the interaction system - where players can hold 'F' to enter interact mode and click on objects - and the port system - where players use Fleet Managers to spawn and store ships at various locations

<p align="center">
  <img src="https://github.com/profdambledore/FoodGame/blob/main/Docs/introImage.jpeg" />
</p>

## Latest Update
<table><tr><td valign="center" width="100%">
 
### v0.14 - TMap to TArray bugfix, Player to Ship Controls
Swapped from using a TMap of FName / Chair Pointer to FShipChairData struct due to a bug causing the pointer in the map to be garbage collected.
 - This also removed the need for the PlayersInSeat map as the struct combines them together
 - Added the FindSeat function to return the index of a seat from a supplied FName SeatName
Added Power Bools to the ship

Added Ship Comtrols to BaseCharacter
 - These all check if ShipSeatedIn is not null before completing their appropriate action
UpdateInteractionWidget now checks if LastInteractedObject is not nullptr before updating

ShipChairButtons now have UpdateButtonEnabled function, which is used to change the state of certain buttons when the power of the ship is turned on or off

Added ShipChairData struct, has FName, ShipChair* and BaseCharatcer* properties

</td></tr></tr></table> 

## Latest Dev Video

<table><tr><td valign="center" width="100%">
 
[![IMAGE ALT TEXT](http://img.youtube.com/vi/D7DjRkftFK8/0.jpg)](https://www.youtube.com/watch?v=D7DjRkftFK8 "Ship Doors")

</td></tr></tr></table> 

## Project Document

[Link](https://github.com/profdambledore/GalaxyExplorer/blob/main/Docs/Galaxy_Explorer.pdf)

## Assets Used:
- Polygon Sci-Fi Space by SyntyStudios 

## Programs Used:
- Unreal Engine 4.26 - Game Engine.
- Visual Studio 2019 - Code Editing.
- Overleaf with LaTeX - Document Creation
- GitHub Desktop - Git Control. 
