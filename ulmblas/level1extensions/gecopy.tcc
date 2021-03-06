#ifndef ULMBLAS_LEVEL1EXTENSIONS_GECOPY_TCC
#define ULMBLAS_LEVEL1EXTENSIONS_GECOPY_TCC 1

#include <ulmblas/auxiliary/conjugate.h>
#include <ulmblas/level1/copy.h>
#include <ulmblas/level1extensions/gecopy.h>

namespace ulmBLAS {

template <typename IndexType, typename MX, typename MY>
void
gecopy(IndexType      m,
       IndexType      n,
       bool           conjX,
       const MX       *X,
       IndexType      incRowX,
       IndexType      incColX,
       MY             *Y,
       IndexType      incRowY,
       IndexType      incColY)
{
    const IndexType    UnitStride(1);

    if (incRowX==UnitStride && incRowY==UnitStride) {
        for (IndexType j=0; j<n; ++j) {
            copy(m, conjX,
                 &X[j*incColX], UnitStride,
                 &Y[j*incColY], UnitStride);
        }
    } else if (incColX==UnitStride && incColY==UnitStride) {
        for (IndexType i=0; i<m; ++i) {
            copy(n, conjX,
                 &X[i*incRowX], UnitStride,
                 &Y[i*incRowY], UnitStride);
        }
    } else {
        for (IndexType j=0; j<n; ++j) {
            for (IndexType i=0; i<m; ++i) {
                Y[i*incRowY+j*incColY] = conjugate(X[i*incRowX+j*incColX],
                                                   conjX);
            }
        }
    }
}

template <typename IndexType, typename MX, typename MY>
void
gecopy(IndexType      m,
       IndexType      n,
       const MX       *X,
       IndexType      incRowX,
       IndexType      incColX,
       MY             *Y,
       IndexType      incRowY,
       IndexType      incColY)
{
    gecopy(m, n, false, X, incRowX, incColX, Y, incRowY, incColY);
}

} // namespace ulmBLAS

#endif // ULMBLAS_LEVEL1EXTENSIONS_GECOPY_TCC 1
