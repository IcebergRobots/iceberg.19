#include "Display.h"

void Display::init() {
  begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialisiere das Displays
  clearDisplay(); // leere den Bildschirm
  if (!silent) drawBitmap(0, 0, LOGO, 114, 64, WHITE); // zeige das Logo
  display();  //wendet Aenderungen an
}

void Display::setupMessage(byte pos, String title, String description) {
  if (!silent) {
    fillRect(47, 0, 81, 31, BLACK); // lösche das Textfeld
    drawRect(0, 29, map(pos, 0, SETUP_MESSAGE_RANGE, 0, 128), 2, WHITE);
    setTextColor(WHITE);

    setTextSize(2);
    setCursor(47, 0);
    print(title.substring(0, 6));

    setTextSize(1);
    setCursor(47, 17);
    print(description.substring(0, 13));

    display();
  }
}

// Infos auf dem Bildschirm anzeigen
void Display::update() {
  if (set() == false) {
    if (DEBUG_FUNCTIONS) debug("reload");
    set();
  }

  clearDisplay();
  setTextColor(WHITE);

  if (level == 0) {
    drawLine(map(page, 0, PAGE_RANGE, 3, 123), 11, map(page, -1, PAGE_RANGE - 1, 3, 123), 11, WHITE);
  } else if (level == 1) {
    drawLine(3, 11, map(subpage, 0, subpageRange[page], 3, 123), 11, WHITE);
    drawLine(map(subpage, -1, subpageRange[page] - 1, 3, 123), 11, 123, 11, WHITE);
  }

  setTextSize(1);
  setCursor(3, 3);
  print(title.substring(0, 14) + String("               ").substring(0, max(1, 15 - title.length())) + runtime);

  setTextSize(2);
  setCursor(3, 14);
  print(line0.substring(0, 10));

  setCursor(3, 30);
  print(line1.substring(0, 10));

  setCursor(3, 46);
  print(line2.substring(0, 10));

  //invertDisplay(m.getMotEn());
  display();      // aktualisiere Display

  //lastDisplay = millis(); // merke Zeitpunkt
}

void Display::select() {
  if (level < 1) {
    level++;
    update();
  }
}

void Display::back() {
  if (level == 0) {
    reset();
  } else {
    level--;
    update();
  }
}

void Display::toggle() {
  if (level == 0) select();
  else back();
}

void Display::change(int change) {
  if (level == 0) {
    page += change;
    shift(page, 0, PAGE_RANGE);
    subpage = 0;
  } else if (level == 1) {
    subpage += change;
    shift(subpage, 0, subpageRange[page]);
  }
  update();
}

bool Display::set() {
  runtime = "";
  int min = numberOfMinutes(millis());
  if (min < 10) {
    runtime += "0";
  }
  runtime += String(min) + ":";
  int sec = numberOfSeconds(millis());
  if (sec < 10) {
    runtime += "0";
  }
  runtime += String(sec);

  title = "";
  line0 = "";
  line1 = "";
  line2 = "";
  lineIndex = 0;

  switch (page) {
    case 0:
      /*if (isTypeA) title = "IcebergRobotsA";
      else*/ title = "IcebergRobotsB";
  }
  if (subpageRange[page] != lineIndex) {
    subpageRange[page] = lineIndex;
    return false;
  } else {
    return true;
  }
}

void Display::addLine(String title, String value) {
  if (title.length() + value.length() < 10) title += String("          ").substring(0, 10 - title.length() - value.length());
  title += value;
  title = title.substring(0, 10);
  int line = lineIndex - subpage;
  shift(line, 0, subpageRange[page]);
  if (line == 0) {
    line0 = title;
  } else if (line == 1) {
    line1 = title;
  } else if (line == 2) {
    line2 = title;
  }
  lineIndex++;

}
void Display::addLine(String title, long value, bool showPlus) {
  if (showPlus) {
    addLine(title, intToStr(value));
  } else {
    addLine(title, String(value));
  }
}
void Display::addLine(String title, long value) {
  addLine(title, String(value));
}
void Display::addLine(String title) {
  addLine(title, "");
}
void Display::addLine() {
  addLine("", "");
}

String Display::intToStr(int number) {
  if (number < 0) {
    return String(number);
  } else {
    return "+" + String(number);
  }
}

byte Display::getPage() {
  return page;
}

Display d = Display(io.test1.getPin());