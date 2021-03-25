#ifndef WEISS_H
#define WEISS_H

#include <flutter/flutter_engine.h>
#include <flutter/method_channel.h>
#include <flutter/standard_method_codec.h>
#include <string.h>

class Weiss
{
private:
  static char *port;
  /* data */
public:
  Weiss()
  {
    port = "9876";
  }
  
  static void bindChannel(flutter::FlutterEngine *flutterEngine,const flutter::StandardMethodCodec *codec);
  static void ser();
  static void start();
  static void stop();
  static void proxy();
};

#endif