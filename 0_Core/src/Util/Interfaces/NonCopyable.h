#ifndef NONCOPYABLEINTERFACE_H
#define NONCOPYABLEINTERFACE_H

class MANGO_API INonCopyable
{
protected:
	INonCopyable()
	{ }

	~INonCopyable()
	{ }

private:
	INonCopyable(const INonCopyable& other) = delete;
	const INonCopyable& operator= (const INonCopyable& other) = delete;
};

#endif
