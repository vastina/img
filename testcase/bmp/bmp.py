import vas_bmp

b = vas_bmp.bmp()
wh = 512
b.resize(wh, wh)
b.filename = "pybind.bmp"

rr1 = ( wh - 1 ) * ( wh - 1 ) - wh
rr2 = ( wh - 1 ) * ( wh - 1 ) + wh

for i in range(b.line):
  offset = i * b.column * 3
  for j in range(b.column):
    rr = (i*i)+(j*j)
    if rr >= rr1 and rr <= rr2 :
      b.setIndex(offset + j * 3, 255)
    else:
      b.setIndex(offset + j * 3, 0)
    b.setIndex(offset + j * 3 + 1, 0)
    b.setIndex(offset + j * 3 + 2, 0)

b.write()