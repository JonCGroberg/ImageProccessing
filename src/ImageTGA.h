#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

struct Header {
  char idLength;        // 1 byte
  char colorMapType;    // 1 byte
  char imageType;       // 1 byte
  short colorMapOrigin; // 2 bytes
  short colorMapLength; // 2 bytes
  char colorMapDepth;   // 1 byte
  short xOrigin;        // 2 bytes
  short yOrigin;        // 2 bytes
  short width;          // 2 bytes:
  short height;         // 2 bytes
  char bitsPerPixel;    // 1 byte
  char imageDescriptor; // 1 byte
};
struct Pixel {
  unsigned char red;   // 1 byte
  unsigned char green; // 1 byte
  unsigned char blue;  // 1 byte

  Pixel operator*(const Pixel &otherPixel) const {
    Pixel result;
    result.red = clamp((int(red) * int(otherPixel.red)) / 255);
    result.green = clamp((int(green) * int(otherPixel.green)) / 255);
    result.blue = clamp((int(blue) * int(otherPixel.blue)) / 255);
    return result;
  }

  Pixel operator-(const Pixel &otherPixel) const {
    Pixel result;
    result.red = clamp((red) - (otherPixel.red));
    result.green = clamp((green) - (otherPixel.green));
    result.blue = clamp((blue) - (otherPixel.blue));
    return result;
  }

  Pixel operator+(const Pixel &otherPixel) const {
    Pixel result;
    result.red = clamp((red) + (otherPixel.red));
    result.green = clamp((green) + (otherPixel.green));
    result.blue = clamp((blue) + (otherPixel.blue));
    return result;
  }

  Pixel overlay(const Pixel &otherPixel) const {
    Pixel result;
    if (red < 128) {
      result.red = (2 * red * otherPixel.red) / 255;
    } else {
      result.red = 255 - 2 * (255 - red) * (255 - otherPixel.red) / 255;
    }
    if (green < 128) {
      result.green = (2 * green * otherPixel.green) / 255;
    } else {
      result.green = 255 - 2 * (255 - green) * (255 - otherPixel.green) / 255;
    }
    if (blue < 128) {
      result.blue = (2 * blue * otherPixel.blue) / 255;
    } else {
      result.blue = 255 - 2 * (255 - blue) * (255 - otherPixel.blue) / 255;
    }
    return result;
  }

  Pixel screen(const Pixel &otherPixel) const {
    Pixel result;
    result.red = 255 - (255 - red) * (255 - otherPixel.red) / 255;
    result.green = 255 - (255 - green) * (255 - otherPixel.green) / 255;
    result.blue = 255 - (255 - blue) * (255 - otherPixel.blue) / 255;
    return result;
  }

  void scale(int r, int g, int b) {
    red = clamp((red * r));
    green = clamp((green * g));
    blue = clamp((blue * b));
  }

  static unsigned char clamp(int channelValue) {
    int max = 255;
    int min = 0;
    channelValue = channelValue < min ? min : channelValue;
    channelValue = channelValue > max ? max : channelValue;
    return (unsigned char)(channelValue);
  }
};

struct ImageTGA {
  Header header;
  vector<Pixel> pixels;
  short width;
  short height;
  ImageTGA(string filePath) { read(filePath); }
  ImageTGA() {}

  ImageTGA add(ImageTGA &otherImage) {
    for (unsigned int i = 0; i < pixels.size(); i++)
      pixels[i] = pixels[i] + otherImage.pixels[i];
    return *this;
  }
  ImageTGA add(Pixel pixel) {
    for (unsigned int i = 0; i < pixels.size(); i++)
      pixels[i] = pixels[i] + pixel;
    return *this;
  }
  ImageTGA multiply(ImageTGA &otherImage) {
    for (unsigned int i = 0; i < pixels.size(); i++)
      pixels[i] = pixels[i] * otherImage.pixels[i];
    return *this;
  }
  ImageTGA scale(int r, int g, int b) {
    for (unsigned int i = 0; i < pixels.size(); i++)
      pixels[i].scale(r, g, b);
    return *this;
  }
  ImageTGA subtract(ImageTGA &otherImage) {
    for (unsigned int i = 0; i < pixels.size(); i++)
      pixels[i] = otherImage.pixels[i] - pixels[i];
    return *this;
  }
  ImageTGA screen(ImageTGA &otherImage) {
    for (unsigned int i = 0; i < pixels.size(); i++)
      pixels[i] = pixels[i].screen(otherImage.pixels[i]);
    return *this;
  }
  ImageTGA overlay(ImageTGA &otherImage) {
    for (unsigned int i = 0; i < pixels.size(); i++)
      pixels[i] = otherImage.pixels[i].overlay(pixels[i]);
    return *this;
  }
  ImageTGA getRedChannel() {
    ImageTGA redChannel;
    redChannel.header = header;
    redChannel.pixels = vector<Pixel>(pixels.size());
    for (unsigned int i = 0; i < pixels.size(); i++) {
      redChannel.pixels[i].red = pixels[i].red;
      redChannel.pixels[i].green = pixels[i].red;
      redChannel.pixels[i].blue = pixels[i].red;
    }
    return redChannel;
  }
  ImageTGA getGreenChannel() {
    ImageTGA greenChannel;
    greenChannel.header = header;
    greenChannel.pixels = vector<Pixel>(pixels.size());
    for (unsigned int i = 0; i < pixels.size(); i++) {
      greenChannel.pixels[i].red = pixels[i].green;
      greenChannel.pixels[i].green = pixels[i].green;
      greenChannel.pixels[i].blue = pixels[i].green;
    }
    return greenChannel;
  }
  ImageTGA getBlueChannel() {
    ImageTGA blueChannel;
    blueChannel.header = header;
    blueChannel.pixels = vector<Pixel>(pixels.size());
    for (unsigned int i = 0; i < pixels.size(); i++) {
      blueChannel.pixels[i].red = pixels[i].blue;
      blueChannel.pixels[i].green = pixels[i].blue;
      blueChannel.pixels[i].blue = pixels[i].blue;
    }
    return blueChannel;
  }
  void rotate180Degrees() {
    vector<Pixel> reversedPixels(pixels.size());
    for (unsigned int i = 0; i < pixels.size(); i++)
      reversedPixels[pixels.size() - i - 1] = pixels[i];
    pixels = reversedPixels;
  }
  void setRedChannel(ImageTGA &redChannel) {
    for (unsigned int i = 0; i < pixels.size(); i++)
      pixels[i].red = redChannel.pixels[i].red;
  }
  void setGreenChannel(ImageTGA &greenChannel) {
    for (unsigned int i = 0; i < pixels.size(); i++)
      pixels[i].green = greenChannel.pixels[i].green;
  }
  void setBlueChannel(ImageTGA &blueChannel) {
    for (unsigned int i = 0; i < pixels.size(); i++)
      pixels[i].blue = blueChannel.pixels[i].blue;
  }
  void print() {
    cout << "Width: " << width << endl;
    cout << "Height: " << height << endl;
    cout << "Number of pixels:" << pixels.size() << endl;
  }
  void write(string filePath) {
    ofstream outputStream(filePath, ios::binary);
    write(outputStream);
    outputStream.close();
  }
  void write(ofstream &file) {
    writeHeader(file, header);
    writeData(file, pixels);
  }
  void read(ifstream &file) {
    header = readHeader(file);
    pixels = readData(file, header.width, header.height);
    width = header.width;
    height = header.height;
  }
  void loadRedChannel() {
    for (unsigned int i = 0; i < pixels.size(); i++) {
      pixels[i].green = 0;
      pixels[i].blue = 0;
    }
  }
  void read(string filePath) {
    ifstream file(filePath, ios::binary);
    read(file);
    file.close();
  }
  Header readHeader(ifstream &file) {
    Header header;
    file.read(&header.idLength, sizeof(header.idLength));
    file.read(&header.colorMapType, sizeof(header.colorMapType));
    file.read(&header.imageType, sizeof(header.imageType));
    file.read(reinterpret_cast<char *>(&header.colorMapOrigin),
              sizeof(header.colorMapOrigin));
    file.read(reinterpret_cast<char *>(&header.colorMapLength),
              sizeof(header.colorMapLength));
    file.read(reinterpret_cast<char *>(&header.colorMapDepth),
              sizeof(header.colorMapDepth));
    file.read(reinterpret_cast<char *>(&header.xOrigin),
              sizeof(header.xOrigin));
    file.read(reinterpret_cast<char *>(&header.yOrigin),
              sizeof(header.yOrigin));
    file.read(reinterpret_cast<char *>(&header.width), sizeof(header.width));
    file.read(reinterpret_cast<char *>(&header.height), sizeof(header.height));
    file.read(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
    file.read(&header.imageDescriptor, sizeof(header.imageDescriptor));
    return header;
  }
  vector<Pixel> readData(ifstream &file, short &width, short &height) {
    vector<Pixel> pixels(width * height);
    for (int i = 0; i < width * height; i++) {
      Pixel pixel;
      file.read(reinterpret_cast<char *>(&pixel.blue), sizeof(pixel.blue));
      file.read(reinterpret_cast<char *>(&pixel.green), sizeof(pixel.green));
      file.read(reinterpret_cast<char *>(&pixel.red), sizeof(pixel.red));
      pixels[i] = pixel;
    }
    return pixels;
  }
  void writeHeader(ofstream &file, Header header) {
    file.write(&header.idLength, sizeof(header.idLength));
    file.write(&header.colorMapType, sizeof(header.colorMapType));
    file.write(&header.imageType, sizeof(header.imageType));
    file.write(reinterpret_cast<char *>(&header.colorMapOrigin),
               sizeof(header.colorMapOrigin));
    file.write(reinterpret_cast<char *>(&header.colorMapLength),
               sizeof(header.colorMapLength));
    file.write(reinterpret_cast<char *>(&header.colorMapDepth),
               sizeof(header.colorMapDepth));
    file.write(reinterpret_cast<char *>(&header.xOrigin),
               sizeof(header.xOrigin));
    file.write(reinterpret_cast<char *>(&header.yOrigin),
               sizeof(header.yOrigin));
    file.write(reinterpret_cast<char *>(&header.width), sizeof(header.width));
    file.write(reinterpret_cast<char *>(&header.height), sizeof(header.height));
    file.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
    file.write(&header.imageDescriptor, sizeof(header.imageDescriptor));
  }
  void writeData(ofstream &file, vector<Pixel> pixels) {
    for (unsigned int i = 0; i < pixels.size(); i++) {
      file.write(reinterpret_cast<char *>(&pixels[i].blue),
                 sizeof(pixels[i].blue));
      file.write(reinterpret_cast<char *>(&pixels[i].green),
                 sizeof(pixels[i].green));
      file.write(reinterpret_cast<char *>(&pixels[i].red),
                 sizeof(pixels[i].red));
    }
  }
};