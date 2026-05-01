import processing.serial.*;
import java.awt.event.KeyEvent;
import java.io.IOException;

Serial myPort;
PFont orcFont;

int iAngle;
int iDistance;

// ===== Store previous detections for object-shape / fade effect =====
class RadarPoint {
  int angle;
  int distance;
  int life;

  RadarPoint(int a, int d) {
    angle = a;
    distance = d;
    life = 255;
  }

  void update() {
    life -= 4;   // smaller = longer trail, larger = faster fade
  }

  boolean isDead() {
    return life <= 0;
  }
}

ArrayList<RadarPoint> points = new ArrayList<RadarPoint>();

void setup() {
  size(1350, 760);
  smooth();

  // Change COM5 to your Arduino port
  myPort = new Serial(this, "COM5", 9600);
  myPort.clear();
  myPort.bufferUntil('\n');

  orcFont = loadFont("OCRAExtended-48.vlw");
}

void draw() {
  fill(98, 245, 31);
  textFont(orcFont);
  noStroke();

  // fade background, keeps radar trail visible
  fill(0, 4);
  rect(0, 0, width, 0.935 * height);

  fill(98, 245, 31);

  DrawRadar();
  DrawLine();
  DrawObject();
  DrawText();
}

void serialEvent(Serial myPort) {
  try {
    String data = myPort.readStringUntil('\n');

    if (data == null) {
      return;
    }

    data = trim(data);
    int commaIndex = data.indexOf(",");

    if (commaIndex == -1) {
      return;
    }

    String angle = data.substring(0, commaIndex);
    String distance = data.substring(commaIndex + 1);

    iAngle = StringToInt(angle);
    iDistance = StringToInt(distance);

    // Add detected point to memory
    if (iDistance < 40 && iDistance != 0) {
      points.add(new RadarPoint(iAngle, iDistance));
    }

  } catch (RuntimeException e) {
  }
}

void DrawRadar() {
  pushMatrix();
  translate(width / 2, 0.926 * height);
  noFill();
  strokeWeight(2);
  stroke(98, 245, 31);

  DrawRadarArcLine(0.9375);
  DrawRadarArcLine(0.7300);
  DrawRadarArcLine(0.5210);
  DrawRadarArcLine(0.3130);

  final int halfWidth = width / 2;
  line(-halfWidth, 0, halfWidth, 0);

  for (int angle = 30; angle <= 150; angle += 30) {
    DrawRadarAngledLine(angle);
  }

  line(-halfWidth * cos(radians(30)), 0, halfWidth, 0);

  popMatrix();
}

void DrawRadarArcLine(final float coefficient) {
  arc(0, 0, coefficient * width, coefficient * width, PI, TWO_PI);
}

void DrawRadarAngledLine(final int angle) {
  line(0, 0, (-width / 2) * cos(radians(angle)), (-width / 2) * sin(radians(angle)));
}

void DrawObject() {
  pushMatrix();
  translate(width / 2, 0.926 * height);

  for (int i = points.size() - 1; i >= 0; i--) {
    RadarPoint p = points.get(i);

    int pixsDistance = int(p.distance * 0.020835 * height);

    float cosVal = cos(radians(p.angle));
    float sinVal = sin(radians(p.angle));

    int x1 = int(pixsDistance * cosVal);
    int y1 = -int(pixsDistance * sinVal);

    int x2 = int(0.495 * width * cosVal);
    int y2 = -int(0.495 * width * sinVal);

    stroke(255, 10, 10, p.life);
    strokeWeight(6);
    line(x1, y1, x2, y2);

    p.update();

    if (p.isDead()) {
      points.remove(i);
    }
  }

  popMatrix();
}

void DrawLine() {
  pushMatrix();
  strokeWeight(9);
  stroke(30, 250, 60);
  translate(width / 2, 0.926 * height);

  float angle = radians(iAngle);
  int x = int(0.88 * height * cos(angle));
  int y = int(-0.88 * height * sin(angle));

  line(0, 0, x, y);

  popMatrix();
}

void DrawText() {
  pushMatrix();

  fill(0, 0, 0);
  noStroke();
  rect(0, 0.9352 * height, width, height);

  fill(98, 245, 31);
  textSize(25);

  text("10cm", 0.6146 * width, 0.9167 * height);
  text("20cm", 0.7190 * width, 0.9167 * height);
  text("30cm", 0.8230 * width, 0.9167 * height);
  text("40cm", 0.9271 * width, 0.9167 * height);

  textSize(40);

  if (iDistance > 40 || iDistance == 0) {
    text("Object: Out of Range", 0.125 * width, 0.9723 * height);
  } else {
    text("Object: In Range", 0.125 * width, 0.9723 * height);
  }

  text("Angle:" + iAngle + "°", 0.52 * width, 0.9723 * height);
  text("Distance:", 0.74 * width, 0.9723 * height);

  if (iDistance < 40 && iDistance != 0) {
    text("        " + iDistance + "cm", 0.775 * width, 0.9723 * height);
  }

  textSize(25);
  fill(98, 245, 60);

  translate(0.5006 * width + width / 2 * cos(radians(30)),
            0.9093 * height - width / 2 * sin(radians(30)));
  rotate(-radians(-60));
  text("30°", 0, 0);

  resetMatrix();

  translate(0.497 * width + width / 2 * cos(radians(60)),
            0.9112 * height - width / 2 * sin(radians(60)));
  rotate(-radians(-30));
  text("60°", 0, 0);

  resetMatrix();

  translate(0.493 * width + width / 2 * cos(radians(90)),
            0.9167 * height - width / 2 * sin(radians(90)));
  rotate(radians(0));
  text("90°", 0, 0);

  resetMatrix();

  translate(0.487 * width + width / 2 * cos(radians(120)),
            0.92871 * height - width / 2 * sin(radians(120)));
  rotate(radians(-30));
  text("120°", 0, 0);

  resetMatrix();

  translate(0.4896 * width + width / 2 * cos(radians(150)),
            0.9426 * height - width / 2 * sin(radians(150)));
  rotate(radians(-60));
  text("150°", 0, 0);

  popMatrix();
}

int StringToInt(String string) {
  int value = 0;

  for (int i = 0; i < string.length(); ++i) {
    if (string.charAt(i) >= '0' && string.charAt(i) <= '9') {
      value *= 10;
      value += (string.charAt(i) - '0');
    }
  }

  return value;
}
