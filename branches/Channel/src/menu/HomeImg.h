#ifndef HOME_IMG_H
#define HOME_IMG_H

class MainWindow;

class HomeImg : public GuiFrame, public CThread, public sigslot::has_slots<>
{
public:
	static void destroyInstance()
	{
		if(homeInstance)
		{
			delete homeInstance;
			homeInstance = NULL;
		}
	}
	
	static void Show(void);
	
private:
	HomeImg();
	~HomeImg();
	
	static HomeImg *homeInstance;
	
	void showHomeImg();
	void hideHomeImg();
	void executeThread();
	void startCountdown();
	
	void OnOpenEffectFinish(GuiElement *element);
	void OnCloseEffectFinish(GuiElement *element);
	
	GuiImageData *imgData;
	GuiImage img;
	
	MainWindow * mainWindow;
	
	int time;
	u64 startTime;
	bool loaded;
	bool exitRequested;
};

#endif
