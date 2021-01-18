#ifndef TYPE_H
#define TYPE_H
#include <string>
class Type
{
public:
	Type(bool isTemp = 1);

	virtual bool isPrintable() const = 0;
	virtual std::string toString() const = 0;
	virtual ~Type() = default;
	void setIsTemp(bool isTemp);
	bool getIsTemp() const;
private:
	bool _isTemp;
};





#endif //TYPE_H
