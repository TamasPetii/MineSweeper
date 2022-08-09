# MineSweeper
![kép](https://user-images.githubusercontent.com/60004480/183734329-d8bc4f08-f497-485d-8304-4378b24784a7.png)
# About the Game
This game was created in c++ made whit Simple DirectMedia Layer (SDL). 
<br><br>
The program has all the algorithms and features that a full value minesweeper program has.
<br><br>
The game map is represented as a one dimensional vector instead of two dimensional vectors.
# About Game Options

| First Header  | Second Header |
| ------------- | ------------- |
| Content Cell  | Content Cell  |
| Content Cell  | Content Cell  |

# About Game Sounds
- Background Music: https://www.youtube.com/watch?v=jyoQu_qxtfE
- Winning Sound: https://www.youtube.com/watch?v=DB8WIdZEHJU
- Losing Sound: https://www.youtube.com/watch?v=aqCxlxclyzo
- Option Click Sound: https://www.youtube.com/watch?v=h6_8SlZZwvQ
- Map Click Sound: https://www.youtube.com/watch?v=gFEbM-8Ypj0
- Error Sound: https://www.youtube.com/watch?v=FwVRkhy5G04

# Installation / Setup (Visual Studio 2022) - Windows
1. Download SDL2 pack: https://www.libsdl.org/release/SDL2-devel-2.0.22-VC.zip
2. Download SDL2_image pack: https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-VC.zip
3. Download SDL2_ttf pack: https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.18-VC.zip
4. Download SDL2_mixer pack: https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.0.4-VC.zip
5. Make a folder in local disk C:\ named as SDL.
6. In C:\SDL folder make folders named as bin, include and lib.
7. Extract the downloaded SDL2 folders and copy their x64 include content to the C:\SDL\include folder. Do the same thing with lib and bin folders (x64!!!). (If lib and bin files are in the same directory of the extracted SDL2 packs then sort them to the proper folds. )
8. At this point your folder should look like this: 

<div align="center">

| Include  | Lib | Bin |
| ------------- | ------------- | ------------- |
| ![kép](https://user-images.githubusercontent.com/60004480/183754634-c33e9a1d-5a21-4651-9e45-6049a18de8ea.png)  | ![kép](https://user-images.githubusercontent.com/60004480/183754683-990298c9-6d11-4184-915e-6e33f571ec4e.png)  | ![kép](https://user-images.githubusercontent.com/60004480/183754762-512b8b76-c5fc-497f-ad55-f5d3ecf4f77f.png)  |
| ![kép](https://user-images.githubusercontent.com/60004480/183754933-45909381-7d28-4c2e-aca1-83309aa0b23e.png) <br> ... (More header files)  | ![kép](https://user-images.githubusercontent.com/60004480/183755009-edfa5503-fd19-482a-a01f-32ad1c146e85.png) <br> (SDLtest might not need!)  | ![kép](https://user-images.githubusercontent.com/60004480/183754843-38f43820-931c-43cf-8b95-0d5d579cca28.png)  |
  
</div>
