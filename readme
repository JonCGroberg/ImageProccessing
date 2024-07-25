# ImageTGA C++ Library for TGA Image Manipulation

This C++ library provides a comprehensive set of tools for working with Truevision TGA (Targa) images in the 24-bit true color, uncompressed format. The library simplifies common image processing tasks such as loading, saving, manipulating pixels, applying blending modes, and extracting color channels.

## Features

- **Image Input/Output:**
  - Read and write TGA images from files
- **Pixel Manipulation:**
  - Add, subtract, multiply, and scale pixel values
  - Clamp pixel values within the valid range
- **Image Operations:**
  - Add, subtract, multiply, and scale images
  - Apply blending modes like screen and overlay
  - Extract red, green, and blue color channels
  - Combine multiple images into a single output
  - Rotate images by 180 degrees
- **Testing:**
  - Built-in test suite to verify results against expected outputs

## Usage

1. **Include Header File:**

   ```c++
   #include "ImageTGA.h"
   ```

2. **Create ImageTGA Objects:**

   ```c++
   ImageTGA image1("input/image1.tga");
   ImageTGA image2("input/image2.tga");
   ```

3. **Perform Operations:**
   ```c++
   ImageTGA result = image1.multiply(image2);
   result.write("output/result.tga");
   ```

## Examples

### Blending Images

```c++
ImageTGA layer1("input/layer1.tga");
ImageTGA pattern1("input/pattern1.tga");
ImageTGA output = layer1.overlay(pattern1);
output.write("output/blended.tga");
```

### Extracting Color Channels

```c++
ImageTGA car("input/car.tga");
ImageTGA redChannel = car.getRedChannel();
redChannel.write("output/car_red.tga");
```

### Combining Images

```c++
ImageTGA car("input/car.tga");
ImageTGA circles("input/circles.tga");
ImageTGA pattern1("input/pattern1.tga");
ImageTGA text("input/text.tga");
ImageTGA output;

output.combineImages(text, pattern1, car, circles);
output.write("output/combined.tga");
```

## Testing

Run the included `tests()` function to verify that the library produces the expected results. This will compare the output images with provided example images.

## Dependencies

- Standard C++ Library (`fstream`, `iostream`, `string`, `vector`, etc.)

## Build and Run

1. Make sure you have a C++ compiler installed (e.g., g++).
2. Place your input TGA images in the `input/` directory.
3. Compile the project:
   ```bash
   g++ main.cpp -o imageProcessor
   ```
4. Run the executable:
   ```bash
   ./imageProcessor
   ```
5. Check the `output/` directory for the results.

## Contributing

Feel free to contribute by submitting pull requests with bug fixes, improvements, or new features.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.
