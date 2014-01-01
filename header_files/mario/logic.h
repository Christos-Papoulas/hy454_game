#ifndef _LOGIC_H_
#define _LOGIC_H_

class Logic {
		private:
				static bool isPaused;
		public:
				static void Create();
				static void Clean();
				static bool IsGamePaused();
};

#endif