#ifndef CONFIG_H
#define CONFIG_H

struct resolution
{
    int x;
    int y;
};

class Config
{
    public:
        Config();
        void LoadConfig();
        resolution GetResolution();
    protected:
    private:
        resolution res;
};

#endif // CONFIG_H
