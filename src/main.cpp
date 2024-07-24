#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
// 24-bit true color, uncompressed TGA
// https://en.wikipedia.org/wiki/Truevision_TGA

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
};

// Read the dimensions of the image
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
  file.read(reinterpret_cast<char *>(&header.xOrigin), sizeof(header.xOrigin));
  file.read(reinterpret_cast<char *>(&header.yOrigin), sizeof(header.yOrigin));
  file.read(reinterpret_cast<char *>(&header.width), sizeof(header.width));
  file.read(reinterpret_cast<char *>(&header.height), sizeof(header.height));
  file.read(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
  file.read(&header.imageDescriptor, sizeof(header.imageDescriptor));
  return header;
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
  file.write(reinterpret_cast<char *>(&header.xOrigin), sizeof(header.xOrigin));
  file.write(reinterpret_cast<char *>(&header.yOrigin), sizeof(header.yOrigin));
  file.write(reinterpret_cast<char *>(&header.width), sizeof(header.width));
  file.write(reinterpret_cast<char *>(&header.height), sizeof(header.height));
  file.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
  file.write(&header.imageDescriptor, sizeof(header.imageDescriptor));
}
// Read the image data
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
void writeData(ofstream &file, vector<Pixel> pixels) {
  for (unsigned int i = 0; i < pixels.size(); i++) {
    file.write(reinterpret_cast<char *>(&pixels[i].blue),
               sizeof(pixels[i].blue));
    file.write(reinterpret_cast<char *>(&pixels[i].green),
               sizeof(pixels[i].green));
    file.write(reinterpret_cast<char *>(&pixels[i].red), sizeof(pixels[i].red));
  }
}

void part1() {
  string outputFilePath = "output/part1.tga";
  string inputDir = "input/";

  string topFilePath = inputDir + "layer1.tga";
  string bottomFilePath = inputDir + "pattern1.tga";

  ifstream topFile(topFilePath, ios::binary);
  ofstream outputFile(outputFilePath, ios::binary);

  Header header = readHeader(topFile);
  vector<Pixel> pixels = readData(topFile, header.width, header.height);

  cout << "Width: " << header.width << endl;
  cout << "Height: " << header.height << endl;
  cout << "Number of pixels: " << pixels.size() << endl;




  cout << "\n Copying File from " << topFilePath << " to " << outputFilePath
       << endl;
  writeHeader(outputFile, header);
  writeData(outputFile, pixels);
}

int main() {
  cout << "--- Running part 1 ---" << endl;
  part1();

  return 0;
}
