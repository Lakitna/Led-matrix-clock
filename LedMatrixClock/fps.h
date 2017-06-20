class fps {
  uint16_t del;
  uint16_t count;
  uint8_t  prev;
  uint16_t frames;
  boolean  newSecondFlag;

  public:
    fps() {
      newSecondFlag = false;
      count=0;
      del=0;
      frames=0;
      prev=0;
    }
    
    byte tick(TimeKeeper t) {
      if (newSecondFlag) newSecondFlag = false;
      
      if (t.s() == prev) count++;
      else {
        frames = count;
        newSecondFlag = true;
        
        count = 0;
        prev = t.s();
      }
      prev = t.s();
    }
    
    void throttle(uint8_t fps_cap, uint8_t variance) {      
      if (newSecondFlag) {
        if (frames > fps_cap) {
          if (frames >= (fps_cap + variance)) del += 10;
          else                                del++;
        }
        else if (frames < (fps_cap - variance) || frames < 1) {
          if (del > 0) del--;
        }
      }

      delay(del);
    }

    unsigned int get() {
      return frames;
    }
    boolean newSecond() {
      return newSecondFlag;
    }
};
