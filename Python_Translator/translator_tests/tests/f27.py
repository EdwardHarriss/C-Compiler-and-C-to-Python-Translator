def f(x):
  return (x + 1)

def g(x):
  return f()

def main():
  g = 4
  return f(2)



if __name__ == '__main__':
  import sys
  ret = main()
  sys.exit(ret)
