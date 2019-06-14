#ifndef __mException__
#define __mException__

class mException
{
    public:
        std::string text;
        mException(const std::string& text) : text(text) {}
};

#endif // define __mException__