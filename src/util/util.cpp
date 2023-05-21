#include "util.hpp"

namespace Game
{

std::tuple<int, int, int, int> RGBAToHSVA(sf::Uint32 rgba) {
   // Convert RGB to normalized values between 0 and 1

   float a = (rgba >> 0 ) & 0xFF;
   float b = (rgba >> 8 ) & 0xFF;
   float g = (rgba >> 16) & 0xFF;
   float r = (rgba >> 24) & 0xFF;

   double normR = r / 255.0;
   double normG = g / 255.0;
   double normB = b / 255.0;
   double normA = a / 255.0;

   double cmax = std::max(normR, std::max(normG, normB));
   double cmin = std::min(normR, std::min(normG, normB));
   double delta = cmax - cmin;

   int hue = 0, saturation = 0, value = 0, alpha = 0;

   // Calculate hue
   if (delta == 0) {
      hue = 0;  // undefined, as RGB is grayscale
   } else if (cmax == normR) {
      hue = static_cast<int>(60 * ((normG - normB) / delta) + 360) % 360;
   } else if (cmax == normG) {
      hue = static_cast<int>(60 * ((normB - normR) / delta) + 120);
   } else if (cmax == normB) {
      hue = static_cast<int>(60 * ((normR - normG) / delta) + 240);
   }

   // Calculate saturation
   if (cmax != 0) {
      saturation = static_cast<int>((delta / cmax) * 100);
   }

   // Calculate value
   value = static_cast<int>(cmax * 100);

   alpha = static_cast<int>(normA * 100);

   return std::make_tuple(hue, saturation, value, alpha);
}

sf::Uint32 HSVAtoRGBA(int hue, int saturation, int value, int alpha) {
   // Normalize hue, saturation, and value to the range [0, 1]
   double normHue = hue / 360.0;
   double normSaturation = saturation / 100.0;
   double normValue = value / 100.0;
   double normAlpha = alpha / 100.0;

   double c = normValue * normSaturation;
   double x = c * (1 - std::abs(std::fmod(6 * normHue, 2) - 1));
   double m = normValue - c;

   double normR = 0, normG = 0, normB = 0;

   if (normHue >= 0 && normHue < 1.0 / 6.0) {
      normR = c;
      normG = x;
   } else if (normHue >= 1.0 / 6.0 && normHue < 2.0 / 6.0) {
      normR = x;
      normG = c;
   } else if (normHue >= 2.0 / 6.0 && normHue < 1.0 / 2.0) {
      normG = c;
      normB = x;
   } else if (normHue >= 1.0 / 2.0 && normHue < 2.0 / 3.0) {
      normG = x;
      normB = c;
   } else if (normHue >= 2.0 / 3.0 && normHue < 5.0 / 6.0) {
      normR = x;
      normB = c;
   } else if (normHue >= 5.0 / 6.0 && normHue <= 1) {
      normR = c;
      normB = x;
   }

   int r = static_cast<int>((normR + m) * 255);
   int g = static_cast<int>((normG + m) * 255);
   int b = static_cast<int>((normB + m) * 255);
   int a = static_cast<int>(normAlpha * 255);

   return (r<<24)+(g<<16)+(b<<8)+a;
}

} // namespace Game
