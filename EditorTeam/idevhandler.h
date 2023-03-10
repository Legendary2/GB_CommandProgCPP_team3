#ifndef IDEVHANDLER_H
#define IDEVHANDLER_H

template <typename T> class IDevHandler {
public:
  virtual bool open() = 0;
  virtual void close() = 0;

  virtual bool save(const T &) = 0;
  virtual bool saveAs(const T &) = 0;

  virtual const T &getSourceName() const = 0;
  virtual const T &getData() const = 0;

  virtual ~IDevHandler() = default;
};

#endif // IDEVHANDLER_H
