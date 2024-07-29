# ImageTGA C++ Library for TGA Image Manipulation

This C++ library provides a comprehensive set of tools for working with Truevision TGA (Targa) images in the 24-bit true color, uncompressed format. The library simplifies common image processing tasks such as loading, saving, manipulating pixels, applying blending modes, and extracting color channels.


## Usage

1. **Create ImageTGA Objects:**

   ```c++
   ImageTGA image1("input/image1.tga");
   ImageTGA image2("input/image2.tga");
   ```

2. **Perform Operations:**
   ```c++
   ImageTGA result = image1.multiply(image2);
   result.write("output/result.tga");
   ```

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

1. Place your input TGA images in the `input/` directory.
2. Compile the project:
     ```bash
     make build 
     ```
3. Run the executable:
     ```bash
     make run
4. Observe output in `output/` directory.

