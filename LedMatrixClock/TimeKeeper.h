class TimeKeeper {
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  unsigned long last_tick;
  unsigned long now;

  public:
    TimeKeeper() {
      String t = F(__TIME__);
      hour   = t.substring(0, 2).toInt();
      minute = t.substring(3, 5).toInt();
      second = t.substring(6).toInt();

      last_tick = millis();
    }

    void tick() {
      now = millis();
      if ((now - last_tick) >= 1000) {
        second++;
        
        if (second >= 60) {
          minute++;
          second=0;
          
          if (minute >= 60) {
            hour++;
            minute=0;
            
            if (hour >= 24) {
              hour=0;
            }
          }
        }
        last_tick += 1000; // increment a second
      }
    }

    byte h() {
      return hour;
    }
    byte m() {
      return minute;
    }
    byte s() {
      return second;
    }
};

