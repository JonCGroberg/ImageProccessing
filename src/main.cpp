#include "ImageTGA.h"
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;
// 24-bit true color, uncompressed TGA
// https://en.wikipedia.org/wiki/Truevision_TGA

// Multiply the images together
void part1() {
  string outputFilePath = "output/part1.tga";
  string inputDir = "input/";

  string topFilePath = inputDir + "layer1.tga";
  string bottomFilePath = inputDir + "pattern1.tga";

  ImageTGA topImage(topFilePath);
  ImageTGA bottomImage(bottomFilePath);
  ImageTGA outputImage;

  // cout << "InputTGA Top: " << topFilePath << endl;
  // topImage.print();
  // cout << "InputTGA Bottom: " << bottomFilePath << endl;
  // topImage.print();

  // cout << "\nMultiplying images..." << endl;
  outputImage = topImage.multiply(bottomImage);

  // cout << "Writing output image..." << endl;
  ofstream outputImageStream(outputFilePath, ios::binary);
  outputImage.write(outputImageStream);

  cout << "Output TGA: " << outputFilePath << endl;
  // outputImage.print();
}
void part2() {
  string outputFilePath = "output/part2.tga";
  string inputDir = "input/";

  string topFilePath = inputDir + "layer2.tga";
  string bottomFilePath = inputDir + "car.tga";

  ImageTGA topImage(topFilePath);
  ImageTGA bottomImage(bottomFilePath);
  ImageTGA outputImage = topImage.subtract(bottomImage);

  outputImage.write(outputFilePath);
  cout << "Output TGA: " << outputFilePath << endl;
  // outputImage.print();
}
void part3() {
  ImageTGA topImage("input/layer1.tga");
  ImageTGA bottomImage("input/pattern2.tga");
  ImageTGA textImage("input/text.tga");
  ImageTGA compositeImage = topImage.multiply(bottomImage);
  ImageTGA outputImage = textImage.screen(compositeImage);

  outputImage.write("output/part3.tga");
  cout << "Output TGA: "
       << "output/part3.tga" << endl;
}
void part4() {
  ImageTGA layer2("input/layer2.tga");
  ImageTGA circles("input/circles.tga");
  ImageTGA pattern2("input/pattern2.tga");

  ImageTGA compositeImage = layer2.multiply(circles);
  ImageTGA outputImage = pattern2.subtract(compositeImage);
  outputImage.write("output/part4.tga");
  cout << "Output TGA: "
       << "output/part4.tga" << endl;
}
void part5() {
  ImageTGA layer1("input/layer1.tga");
  ImageTGA pattern1("input/pattern1.tga");

  ImageTGA outputImage = layer1.overlay(pattern1);
  outputImage.write("output/part5.tga");
  cout << "Output TGA: "
       << "output/part5.tga" << endl;
}
void part6() {
  ImageTGA car("input/car.tga");
  Pixel green200 = {0, 200, 0};
  car.add(green200);

  car.write("output/part6.tga");
  cout << "Output TGA: "
       << "output/part6.tga" << endl;
}
void part7() {
  ImageTGA car("input/car.tga");
  car.scale(4, 1, 0);

  car.write("output/part7.tga");
  cout << "Output TGA: "
       << "output/part7.tga" << endl;
}
void part8() {
  ImageTGA car("input/car.tga");
  ImageTGA redChannel = car.getRedChannel();
  ImageTGA greenChannel = car.getGreenChannel();
  ImageTGA blueChannel = car.getBlueChannel();

  redChannel.write("output/part8_r.tga");
  greenChannel.write("output/part8_g.tga");
  blueChannel.write("output/part8_b.tga");

  cout << "Output TGA: "
       << "output/part8_r.tga" << endl;
  cout << "Output TGA: "
       << "output/part8_g.tga" << endl;
  cout << "Output TGA: "
       << "output/part8_b.tga" << endl;
}
void part9() {
  ImageTGA redChannel("input/layer_red.tga");
  ImageTGA greenChannel("input/layer_green.tga");
  ImageTGA blueChannel("input/layer_blue.tga");
  ImageTGA outputImage = redChannel;

  outputImage.setGreenChannel(greenChannel);
  outputImage.setBlueChannel(blueChannel);

  outputImage.write("output/part9.tga");
  cout << "Output TGA: "
       << "output/part9.tga" << endl;
}
void part10() {
  ImageTGA text2Image("input/text2.tga");
  text2Image.rotate180Degrees();
  text2Image.write("output/part10.tga");
  cout << "Output TGA: "
       << "output/part10.tga" << endl;
}

void tests(){

}

int main() {
  cout << "--- Running part 1 ---" << endl;
  part1();
  cout << "--- Running part 2 ---" << endl;
  part2();
  cout << "--- Running part 3 ---" << endl;
  part3();
  cout << "--- Running part 4 ---" << endl;
  part4();
  cout << "--- Running part 5 ---" << endl;
  part5();
  cout << "--- Running part 6 ---" << endl;
  part6();
  cout << "--- Running part 7 ---" << endl;
  part7();
  cout << "--- Running part 8 ---" << endl;
  part8();
  cout << "--- Running part 9 ---" << endl;
  part9();
  cout << "--- Running part 10 ---" << endl;
  part10();
  cout << "--- Done ---" << endl;

  cout << "Running Tests" << endl;

  return 0;
}
