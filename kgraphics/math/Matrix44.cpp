#include <stdafx.h>

#include <kgraphics/math/Matrix33.h>
#include <kgraphics/math/Matrix44.h>
#include <kgraphics/math/math.h>
#include <kgraphics/math/Quat.h>
#include <kgraphics/math/Vector3.h>
#include <kgraphics/math/Vector4.h>

namespace gfx {

//-------------------------------------------------------------------------------
// @ Matrix44::Matrix44()
//-------------------------------------------------------------------------------
// Axis-angle constructor
//-------------------------------------------------------------------------------
Matrix44::Matrix44( const Quat& quat )
{
    (void) Rotation( quat );

}   // End of Matrix44::Matrix44()


//-------------------------------------------------------------------------------
// @ Matrix44::Matrix44()
//-------------------------------------------------------------------------------
// Copy constructor
//-------------------------------------------------------------------------------
Matrix44::Matrix44(const Matrix44& other)
{
    mV[0] = other.mV[0];
    mV[1] = other.mV[1];
    mV[2] = other.mV[2];
    mV[3] = other.mV[3];
    mV[4] = other.mV[4];
    mV[5] = other.mV[5];
    mV[6] = other.mV[6];
    mV[7] = other.mV[7];
    mV[8] = other.mV[8];
    mV[9] = other.mV[9];
    mV[10] = other.mV[10];
    mV[11] = other.mV[11];
    mV[12] = other.mV[12];
    mV[13] = other.mV[13];
    mV[14] = other.mV[14];
    mV[15] = other.mV[15];

}   // End of Matrix44::Matrix44()

//-------------------------------------------------------------------------------
// @ Matrix44::Matrix44()
//-------------------------------------------------------------------------------
// Matrix33 conversion constructor
//-------------------------------------------------------------------------------
Matrix44::Matrix44(const Matrix33& other)
{
    (void) Rotation( other );

}   // End of Matrix44::Matrix44()


//-------------------------------------------------------------------------------
// @ Matrix44::operator=()
//-------------------------------------------------------------------------------
// Assignment operator
//-------------------------------------------------------------------------------
Matrix44&
Matrix44::operator=(const Matrix44& other)
{
    // if same object
    if ( this == &other )
        return *this;
        
    mV[0] = other.mV[0];
    mV[1] = other.mV[1];
    mV[2] = other.mV[2];
    mV[3] = other.mV[3];
    mV[4] = other.mV[4];
    mV[5] = other.mV[5];
    mV[6] = other.mV[6];
    mV[7] = other.mV[7];
    mV[8] = other.mV[8];
    mV[9] = other.mV[9];
    mV[10] = other.mV[10];
    mV[11] = other.mV[11];
    mV[12] = other.mV[12];
    mV[13] = other.mV[13];
    mV[14] = other.mV[14];
    mV[15] = other.mV[15];
    
    return *this;

}   // End of Matrix44::operator=()


//-------------------------------------------------------------------------------
// @ operator<<()
//-------------------------------------------------------------------------------
// Text output for debugging
//-------------------------------------------------------------------------------
Writer& 
operator<<(Writer& out, const Matrix44& source)
{
    // row
    for (unsigned int i = 0; i < 4; ++i)
    {
        out << "| ";
        // column
        for (unsigned int j = 0; j < 4; ++j )
        {
            out << source.mV[ j*4 + i ] << ' ';
        }
        out << '|' << eol;
    }

    return out;
    
}   // End of operator<<()
    

//-------------------------------------------------------------------------------
// @ Matrix44::operator==()
//-------------------------------------------------------------------------------
// Comparison operator
//-------------------------------------------------------------------------------
bool 
Matrix44::operator==( const Matrix44& other ) const
{
    for (unsigned int i = 0; i < 16; ++i)
    {
        if ( !AreEqual(mV[i], other.mV[i]) )
            return false;
    }
    return true;

}   // End of Matrix44::operator==()


//-------------------------------------------------------------------------------
// @ Matrix44::operator!=()
//-------------------------------------------------------------------------------
// Comparison operator
//-------------------------------------------------------------------------------
bool 
Matrix44::operator!=( const Matrix44& other ) const
{
    for (unsigned int i = 0; i < 16; ++i)
    {
        if ( !AreEqual(mV[i], other.mV[i]) )
            return true;
    }
    return false;

}   // End of Matrix44::operator!=()


//-------------------------------------------------------------------------------
// @ Matrix44::IsZero()
//-------------------------------------------------------------------------------
// Check for zero matrix
//-------------------------------------------------------------------------------
bool 
Matrix44::IsZero() const
{
    for (unsigned int i = 0; i < 16; ++i)
    {
        if ( !gfx::IsZero( mV[i] ) )
            return false;
    }
    return true;

}   // End of Matrix44::IsZero()


//-------------------------------------------------------------------------------
// @ Matrix44::IsIdentity()
//-------------------------------------------------------------------------------
// Check for identity matrix
//-------------------------------------------------------------------------------
bool 
Matrix44::IsIdentity() const
{
    return AreEqual( 1.0f, mV[0] )
        && AreEqual( 1.0f, mV[5] )
        && AreEqual( 1.0f, mV[10] )
        && AreEqual( 1.0f, mV[15] )
        && gfx::IsZero( mV[1] ) 
        && gfx::IsZero( mV[2] )
        && gfx::IsZero( mV[3] )
        && gfx::IsZero( mV[4] ) 
        && gfx::IsZero( mV[6] )
        && gfx::IsZero( mV[7] )
        && gfx::IsZero( mV[8] )
        && gfx::IsZero( mV[9] )
        && gfx::IsZero( mV[11] )
        && gfx::IsZero( mV[12] )
        && gfx::IsZero( mV[13] )
        && gfx::IsZero( mV[14] );

}   // End of Matrix44::IsIdentity()


//-------------------------------------------------------------------------------
// @ Matrix44::Clean()
//-------------------------------------------------------------------------------
// Set elements close to zero equal to zero
//-------------------------------------------------------------------------------
void
Matrix44::Clean()
{
    for (unsigned int i = 0; i < 16; ++i)
    {
        if ( gfx::IsZero( mV[i] ) )
            mV[i] = 0.0f;
    }

}   // End of Matrix44::Clean()


//-------------------------------------------------------------------------------
// @ Matrix44::Identity()
//-------------------------------------------------------------------------------
// Set to identity matrix
//-------------------------------------------------------------------------------
void
Matrix44::Identity()
{
    mV[0] = 1.0f;
    mV[1] = 0.0f;
    mV[2] = 0.0f;
    mV[3] = 0.0f;
    mV[4] = 0.0f;
    mV[5] = 1.0f;
    mV[6] = 0.0f;
    mV[7] = 0.0f;
    mV[8] = 0.0f;
    mV[9] = 0.0f;
    mV[10] = 1.0f;
    mV[11] = 0.0f;
    mV[12] = 0.0f;
    mV[13] = 0.0f;
    mV[14] = 0.0f;
    mV[15] = 1.0f;

}   // End of Matrix44::Identity()


//-----------------------------------------------------------------------------
// @ Matrix44::AffineInverse()
//-----------------------------------------------------------------------------
/// Set self to matrix inverse, assuming a standard affine matrix 
/// (bottom row is 0 0 0 1)
//-----------------------------------------------------------------------------
Matrix44& 
Matrix44::AffineInverse()
{
    *this = gfx::AffineInverse( *this );
    
    return *this;

}   // End of Matrix44::AffineInverse()


//-----------------------------------------------------------------------------
// @ AffineInverse()
//-----------------------------------------------------------------------------
/// Compute matrix inverse, assuming a standard affine matrix 
/// (bottom row is 0 0 0 1)
//-----------------------------------------------------------------------------
Matrix44 
AffineInverse( const Matrix44& mat )
{
    Matrix44 result;
    
    // compute upper left 3x3 matrix determinant
    float cofactor0 = mat.mV[5]*mat.mV[10] - mat.mV[6]*mat.mV[9];
    float cofactor4 = mat.mV[2]*mat.mV[9] - mat.mV[1]*mat.mV[10];
    float cofactor8 = mat.mV[1]*mat.mV[6] - mat.mV[2]*mat.mV[5];
    float det = mat.mV[0]*cofactor0 + mat.mV[4]*cofactor4 + mat.mV[8]*cofactor8;
    if (gfx::IsZero( det ))
    {
        return result;
    }

    // create adjunct matrix and multiply by 1/det to get upper 3x3
    float invDet = 1.0f/det;
    result.mV[0] = invDet*cofactor0;
    result.mV[1] = invDet*cofactor4;
    result.mV[2] = invDet*cofactor8;
   
    result.mV[4] = invDet*(mat.mV[6]*mat.mV[8] - mat.mV[4]*mat.mV[10]);
    result.mV[5] = invDet*(mat.mV[0]*mat.mV[10] - mat.mV[2]*mat.mV[8]);
    result.mV[6] = invDet*(mat.mV[2]*mat.mV[4] - mat.mV[0]*mat.mV[6]);

    result.mV[8] = invDet*(mat.mV[4]*mat.mV[9] - mat.mV[5]*mat.mV[8]);
    result.mV[9] = invDet*(mat.mV[1]*mat.mV[8] - mat.mV[0]*mat.mV[9]);
    result.mV[10] = invDet*(mat.mV[0]*mat.mV[5] - mat.mV[1]*mat.mV[4]);

    // multiply -translation by inverted 3x3 to get its inverse
    
    result.mV[12] = -result.mV[0]*mat.mV[12] - result.mV[4]*mat.mV[13] - result.mV[8]*mat.mV[14];
    result.mV[13] = -result.mV[1]*mat.mV[12] - result.mV[5]*mat.mV[13] - result.mV[9]*mat.mV[14];
    result.mV[14] = -result.mV[2]*mat.mV[12] - result.mV[6]*mat.mV[13] - result.mV[10]*mat.mV[14];

    return result;

}   // End of AffineInverse()


//-------------------------------------------------------------------------------
// @ Matrix44::Transpose()
//-------------------------------------------------------------------------------
// Set self to transpose
//-------------------------------------------------------------------------------
Matrix44& 
Matrix44::Transpose()
{
    float temp = mV[1];
    mV[1] = mV[4];
    mV[4] = temp;

    temp = mV[2];
    mV[2] = mV[8];
    mV[8] = temp;

    temp = mV[3];
    mV[2] = mV[12];
    mV[12] = temp;

    temp = mV[6];
    mV[6] = mV[9];
    mV[9] = temp;

    temp = mV[7];
    mV[7] = mV[13];
    mV[13] = temp;

    temp = mV[11];
    mV[11] = mV[14];
    mV[14] = temp;

    return *this;

}   // End of Matrix44::Transpose()


//-------------------------------------------------------------------------------
// @ Transpose()
//-------------------------------------------------------------------------------
// Compute matrix transpose
//-------------------------------------------------------------------------------
Matrix44 
Transpose( const Matrix44& mat )
{
    Matrix44 result;

    result.mV[0] = mat.mV[0];
    result.mV[1] = mat.mV[4];
    result.mV[2] = mat.mV[8];
    result.mV[3] = mat.mV[12];
    result.mV[4] = mat.mV[1];
    result.mV[5] = mat.mV[5];
    result.mV[6] = mat.mV[9];
    result.mV[7] = mat.mV[13];
    result.mV[8] = mat.mV[2];
    result.mV[9] = mat.mV[6];
    result.mV[10] = mat.mV[10];
    result.mV[11] = mat.mV[14];
    result.mV[12] = mat.mV[3];
    result.mV[13] = mat.mV[7];
    result.mV[14] = mat.mV[11];
    result.mV[15] = mat.mV[15];

    return result;

}   // End of Transpose()


//-------------------------------------------------------------------------------
// @ Matrix44::Translation()
//-------------------------------------------------------------------------------
// Set as translation matrix based on vector
//-------------------------------------------------------------------------------
Matrix44& 
Matrix44::Translation( const Vector3& xlate )
{
    mV[0] = 1.0f;
    mV[1] = 0.0f;
    mV[2] = 0.0f;
    mV[3] = 0.0f;
    mV[4] = 0.0f;
    mV[5] = 1.0f;
    mV[6] = 0.0f;
    mV[7] = 0.0f;
    mV[8] = 0.0f;
    mV[9] = 0.0f;
    mV[10] = 1.0f;
    mV[11] = 0.0f;
    mV[12] = xlate.x;
    mV[13] = xlate.y;
    mV[14] = xlate.z;
    mV[15] = 1.0f;

    return *this;

}   // End of Matrix44::Translation()


//-------------------------------------------------------------------------------
// @ Matrix44::Rotation()
//-------------------------------------------------------------------------------
// Set as rotation matrix based on quaternion
//-------------------------------------------------------------------------------
Matrix44& 
Matrix44::Rotation( const Quat& rotate )
{
    // //ASSERT( rotate.IsUnit() );

    float xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz;

    xs = rotate.x+rotate.x;   
    ys = rotate.y+rotate.y;
    zs = rotate.z+rotate.z;
    wx = rotate.w*xs;
    wy = rotate.w*ys;
    wz = rotate.w*zs;
    xx = rotate.x*xs;
    xy = rotate.x*ys;
    xz = rotate.x*zs;
    yy = rotate.y*ys;
    yz = rotate.y*zs;
    zz = rotate.z*zs;

    mV[0] = 1.0f - (yy + zz);
    mV[4] = xy - wz;
    mV[8] = xz + wy;
    mV[12] = 0.0f;
    
    mV[1] = xy + wz;
    mV[5] = 1.0f - (xx + zz);
    mV[9] = yz - wx;
    mV[13] = 0.0f;
    
    mV[2] = xz - wy;
    mV[6] = yz + wx;
    mV[10] = 1.0f - (xx + yy);
    mV[14] = 0.0f;

    mV[3] = 0.0f;
    mV[7] = 0.0f;
    mV[11] = 0.0f;
    mV[15] = 1.0f;

    return *this;

}   // End of Rotation()


//-------------------------------------------------------------------------------
// @ Matrix44::Rotation()
//-------------------------------------------------------------------------------
// Set to rotation matrix based on 3x3 matrix (which better be a rotation)
//-------------------------------------------------------------------------------
Matrix44&
Matrix44::Rotation(const Matrix33& other)
{
    mV[0] = other.mV[0];
    mV[1] = other.mV[1];
    mV[2] = other.mV[2];
    mV[3] = 0;
    mV[4] = other.mV[3];
    mV[5] = other.mV[4];
    mV[6] = other.mV[5];
    mV[7] = 0;
    mV[8] = other.mV[6];
    mV[9] = other.mV[7];
    mV[10] = other.mV[8];
    mV[11] = 0;
    mV[12] = 0;
    mV[13] = 0;
    mV[14] = 0;
    mV[15] = 1;

    return *this;

}   // End of Matrix44::Matrix44()


//----------------------------------------------------------------------------
// @ Matrix44::Rotation()
// ---------------------------------------------------------------------------
// Sets the matrix to a rotation matrix (by Euler angles).
//----------------------------------------------------------------------------
Matrix44 &
Matrix44::Rotation( float zRotation, float yRotation, float xRotation )
{
    // This is an "unrolled" contatenation of rotation matrices X Y & Z
    float Cx, Sx;
    SinCos(xRotation, Sx, Cx);

    float Cy, Sy;
    SinCos(yRotation, Sy, Cy);

    float Cz, Sz;
    SinCos(zRotation, Sz, Cz);

    mV[0] =  (Cy * Cz);
    mV[4] = -(Cy * Sz);  
    mV[8] =  Sy;
    mV[12] = 0.0f;

    mV[1] =  (Sx * Sy * Cz) + (Cx * Sz);
    mV[5] = -(Sx * Sy * Sz) + (Cx * Cz);
    mV[9] = -(Sx * Cy); 
    mV[13] = 0.0f;

    mV[2] = -(Cx * Sy * Cz) + (Sx * Sz);
    mV[6] =  (Cx * Sy * Sz) + (Sx * Cz);
    mV[10] =  (Cx * Cy);
    mV[14] = 0.0f;

    mV[3] = 0.0f;
    mV[7] = 0.0f;
    mV[11] = 0.0f;
    mV[15] = 1.0f;

    return *this;

}  // End of Matrix44::Rotation()


//----------------------------------------------------------------------------
// @ Matrix44::Rotation()
// ---------------------------------------------------------------------------
// Sets the matrix to a rotation matrix (by axis and angle).
//----------------------------------------------------------------------------
Matrix44 &
Matrix44::Rotation( const Vector3& axis, float angle )
{
    float c, s;
    SinCos(angle, s, c);
    float t = 1.0f - c;

    Vector3 nAxis = axis;
    nAxis.Normalize();

    // intermediate values
    float tx = t*nAxis.x;  float ty = t*nAxis.y;  float tz = t*nAxis.z;
    float sx = s*nAxis.x;  float sy = s*nAxis.y;  float sz = s*nAxis.z;
    float txy = tx*nAxis.y; float tyz = tx*nAxis.z; float txz = tx*nAxis.z;

    // set matrix
    mV[0] = tx*nAxis.x + c;
    mV[4] = txy - sz; 
    mV[8] = txz + sy;
    mV[12] = 0.0f;

    mV[1] = txy + sz;
    mV[5] = ty*nAxis.y + c;
    mV[9] = tyz - sx;
    mV[13] = 0.0f;

    mV[2] = txz - sy;
    mV[6] = tyz + sx;
    mV[10] = tz*nAxis.z + c;
    mV[14] = 0.0f;

    mV[3] = 0.0f;
    mV[7] = 0.0f;
    mV[11] = 0.0f;
    mV[15] = 1.0f;

    return *this;

}  // End of Matrix44::Rotation()


//-------------------------------------------------------------------------------
// @ Matrix44::Scaling()
//-------------------------------------------------------------------------------
// Set as scaling matrix based on vector
//-------------------------------------------------------------------------------
Matrix44& 
Matrix44::Scaling( const Vector3& scaleFactors )
{
    mV[0] = scaleFactors.x;
    mV[1] = 0.0f;
    mV[2] = 0.0f;
    mV[3] = 0.0f;
    mV[4] = 0.0f;
    mV[5] = scaleFactors.y;
    mV[6] = 0.0f;
    mV[7] = 0.0f;
    mV[8] = 0.0f;
    mV[9] = 0.0f;
    mV[10] = scaleFactors.z;
    mV[11] = 0.0f;
    mV[12] = 0.0f;
    mV[13] = 0.0f;
    mV[14] = 0.0f;
    mV[15] = 1.0f;

    return *this;

}   // End of Scaling()


//-------------------------------------------------------------------------------
// @ Matrix44::RotationX()
//-------------------------------------------------------------------------------
// Set as rotation matrix, rotating by 'angle' radians around x-axis
//-------------------------------------------------------------------------------
Matrix44& 
Matrix44::RotationX( float angle )
{
    float sintheta, costheta;
    SinCos(angle, sintheta, costheta);

    mV[0] = 1.0f;
    mV[1] = 0.0f;
    mV[2] = 0.0f;
    mV[3] = 0.0f;
    mV[4] = 0.0f;
    mV[5] = costheta;
    mV[6] = sintheta;
    mV[7] = 0.0f;
    mV[8] = 0.0f;
    mV[9] = -sintheta;
    mV[10] = costheta;
    mV[11] = 0.0f;
    mV[12] = 0.0f;
    mV[13] = 0.0f;
    mV[14] = 0.0f;
    mV[15] = 1.0f;

    return *this;

}   // End of RotationX()


//-------------------------------------------------------------------------------
// @ Matrix44::RotationY()
//-------------------------------------------------------------------------------
// Set as rotation matrix, rotating by 'angle' radians around y-axis
//-------------------------------------------------------------------------------
Matrix44& 
Matrix44::RotationY( float angle )
{
    float sintheta, costheta;
    SinCos(angle, sintheta, costheta);

    mV[0] = costheta;
    mV[1] = 0.0f;
    mV[2] = -sintheta;
    mV[3] = 0.0f;
    mV[4] = 0.0f;
    mV[5] = 1.0f;
    mV[6] = 0.0f;
    mV[7] = 0.0f;
    mV[8] = sintheta;
    mV[9] = 0.0f;
    mV[10] = costheta;
    mV[11] = 0.0f;
    mV[12] = 0.0f;
    mV[13] = 0.0f;
    mV[14] = 0.0f;
    mV[15] = 1.0f;    

    return *this;

}   // End of RotationY()


//-------------------------------------------------------------------------------
// @ Matrix44::RotationZ()
//-------------------------------------------------------------------------------
// Set as rotation matrix, rotating by 'angle' radians around z-axis
//-------------------------------------------------------------------------------
Matrix44& 
Matrix44::RotationZ( float angle )
{
    float sintheta, costheta;
    SinCos(angle, sintheta, costheta);

    mV[0] = costheta;
    mV[1] = sintheta;
    mV[2] = 0.0f;
    mV[3] = 0.0f;
    mV[4] = -sintheta;
    mV[5] = costheta;
    mV[6] = 0.0f;
    mV[7] = 0.0f;
    mV[8] = 0.0f;
    mV[9] = 0.0f;
    mV[10] = 1.0f;
    mV[11] = 0.0f;
    mV[12] = 0.0f;
    mV[13] = 0.0f;
    mV[14] = 0.0f;
    mV[15] = 1.0f;

    return *this;

}   // End of RotationZ()


//----------------------------------------------------------------------------
// @ Matrix44::GetFixedAngles()
// ---------------------------------------------------------------------------
// Gets one set of possible z-y-x fixed angles that will generate this matrix
// Assumes that upper 3x3 is a rotation matrix
//----------------------------------------------------------------------------
void
Matrix44::GetFixedAngles( float& zRotation, float& yRotation, float& xRotation )
{
    float Cx, Sx;
    float Cy, Sy;
    float Cz, Sz;

    Sy = mV[8];
    Cy = Sqrt( 1.0f - Sy*Sy );
    // normal case
    if ( !gfx::IsZero( Cy ) )
    {
        float factor = 1.0f/Cy;
        Sx = -mV[9]*factor;
        Cx = mV[10]*factor;
        Sz = -mV[4]*factor;
        Cz = mV[0]*factor;
    }
    // x and z axes aligned
    else
    {
        Sz = 0.0f;
        Cz = 1.0f;
        Sx = mV[6];
        Cx = mV[5];
    }

    zRotation = atan2f( Sz, Cz );
    yRotation = atan2f( Sy, Cy );
    xRotation = atan2f( Sx, Cx );

}  // End of Matrix44::GetFixedAngles()


//----------------------------------------------------------------------------
// @ Matrix44::GetAxisAngle()
// ---------------------------------------------------------------------------
// Gets one possible axis-angle pair that will generate this matrix
// Assumes that upper 3x3 is a rotation matrix
//----------------------------------------------------------------------------
void
Matrix44::GetAxisAngle( Vector3& axis, float& angle )
{
    float trace = mV[0] + mV[5] + mV[10];
    float cosTheta = 0.5f*(trace - 1.0f);
    angle = acosf( cosTheta );

    // angle is zero, axis can be anything
    if ( gfx::IsZero( angle ) )
    {
        axis = Vector3::xAxis;
    }
    // standard case
    else if ( angle < kPI-kEpsilon )
    {
        axis.Set( mV[6]-mV[9], mV[8]-mV[2], mV[1]-mV[4] );
        axis.Normalize();
    }
    // angle is 180 degrees
    else
    {
        unsigned int i = 0;
        if ( mV[5] > mV[0] )
            i = 1;
        if ( mV[10] > mV[i + 4*i] )
            i = 2;
        unsigned int j = (i+1)%3;
        unsigned int k = (j+1)%3;
        float s = Sqrt( mV[i + 4*i] - mV[j + 4*j] - mV[k + 4*k] + 1.0f );
        axis[i] = 0.5f*s;
        float recip = 1.0f/s;
        axis[j] = (mV[i + 4*j])*recip;
        axis[k] = (mV[k + 4*i])*recip;
    }

}  // End of Matrix44::GetAxisAngle()


//-------------------------------------------------------------------------------
// @ Matrix44::operator+()
//-------------------------------------------------------------------------------
// Matrix addition 
//-------------------------------------------------------------------------------
Matrix44
Matrix44::operator+( const Matrix44& other ) const
{
    Matrix44 result;

    for (unsigned int i = 0; i < 16; ++i)
    {
        result.mV[i] = mV[i] + other.mV[i];
    }

    return result;

}   // End of Matrix44::operator-()


//-------------------------------------------------------------------------------
// @ Matrix44::operator+=()
//-------------------------------------------------------------------------------
// Matrix addition by self
//-------------------------------------------------------------------------------
Matrix44&
Matrix44::operator+=( const Matrix44& other )
{
    for (unsigned int i = 0; i < 16; ++i)
    {
        mV[i] += other.mV[i];
    }

    return *this;

}   // End of Matrix44::operator+=()


//-------------------------------------------------------------------------------
// @ Matrix44::operator-()
//-------------------------------------------------------------------------------
// Matrix subtraction 
//-------------------------------------------------------------------------------
Matrix44
Matrix44::operator-( const Matrix44& other ) const
{
    Matrix44 result;

    for (unsigned int i = 0; i < 16; ++i)
    {
        result.mV[i] = mV[i] - other.mV[i];
    }

    return result;

}   // End of Matrix44::operator-()


//-------------------------------------------------------------------------------
// @ Matrix44::operator-=()
//-------------------------------------------------------------------------------
// Matrix subtraction by self
//-------------------------------------------------------------------------------
Matrix44&
Matrix44::operator-=( const Matrix44& other )
{
    for (unsigned int i = 0; i < 16; ++i)
    {
        mV[i] -= other.mV[i];
    }

    return *this;

}   // End of Matrix44::operator-=()


//-------------------------------------------------------------------------------
// @ Matrix44::operator-=() (unary)
//-------------------------------------------------------------------------------
// Negate self and return
//-------------------------------------------------------------------------------
Matrix44
Matrix44::operator-() const
{
    Matrix44 result;

    for (unsigned int i = 0; i < 16; ++i)
    {
        result.mV[i] = -mV[i];
    }

    return result;

}    // End of Quat::operator-()


//-------------------------------------------------------------------------------
// @ Matrix44::operator*()
//-------------------------------------------------------------------------------
// Matrix multiplication
//-------------------------------------------------------------------------------
Matrix44  
Matrix44::operator*( const Matrix44& other ) const
{
    Matrix44 result;

    result.mV[0] = mV[0]*other.mV[0] + mV[4]*other.mV[1] + mV[8]*other.mV[2] 
                    + mV[12]*other.mV[3];
    result.mV[1] = mV[1]*other.mV[0] + mV[5]*other.mV[1] + mV[9]*other.mV[2] 
                    + mV[13]*other.mV[3];
    result.mV[2] = mV[2]*other.mV[0] + mV[6]*other.mV[1] + mV[10]*other.mV[2] 
                    + mV[14]*other.mV[3];
    result.mV[3] = mV[3]*other.mV[0] + mV[7]*other.mV[1] + mV[11]*other.mV[2] 
                    + mV[15]*other.mV[3];

    result.mV[4] = mV[0]*other.mV[4] + mV[4]*other.mV[5] + mV[8]*other.mV[6] 
                    + mV[12]*other.mV[7];
    result.mV[5] = mV[1]*other.mV[4] + mV[5]*other.mV[5] + mV[9]*other.mV[6] 
                    + mV[13]*other.mV[7];
    result.mV[6] = mV[2]*other.mV[4] + mV[6]*other.mV[5] + mV[10]*other.mV[6] 
                    + mV[14]*other.mV[7];
    result.mV[7] = mV[3]*other.mV[4] + mV[7]*other.mV[5] + mV[11]*other.mV[6] 
                    + mV[15]*other.mV[7];

    result.mV[8] = mV[0]*other.mV[8] + mV[4]*other.mV[9] + mV[8]*other.mV[10] 
                    + mV[12]*other.mV[11];
    result.mV[9] = mV[1]*other.mV[8] + mV[5]*other.mV[9] + mV[9]*other.mV[10] 
                    + mV[13]*other.mV[11];
    result.mV[10] = mV[2]*other.mV[8] + mV[6]*other.mV[9] + mV[10]*other.mV[10] 
                    + mV[14]*other.mV[11];
    result.mV[11] = mV[3]*other.mV[8] + mV[7]*other.mV[9] + mV[11]*other.mV[10] 
                    + mV[15]*other.mV[11];

    result.mV[12] = mV[0]*other.mV[12] + mV[4]*other.mV[13] + mV[8]*other.mV[14] 
                    + mV[12]*other.mV[15];
    result.mV[13] = mV[1]*other.mV[12] + mV[5]*other.mV[13] + mV[9]*other.mV[14] 
                    + mV[13]*other.mV[15];
    result.mV[14] = mV[2]*other.mV[12] + mV[6]*other.mV[13] + mV[10]*other.mV[14] 
                    + mV[14]*other.mV[15];
    result.mV[15] = mV[3]*other.mV[12] + mV[7]*other.mV[13] + mV[11]*other.mV[14] 
                    + mV[15]*other.mV[15];

    return result;

}   // End of Matrix44::operator*()


//-------------------------------------------------------------------------------
// @ Matrix44::operator*=()
//-------------------------------------------------------------------------------
// Matrix multiplication by self
//-------------------------------------------------------------------------------
Matrix44&
Matrix44::operator*=( const Matrix44& other )
{
    Matrix44 result;

    result.mV[0] = mV[0]*other.mV[0] + mV[4]*other.mV[1] + mV[8]*other.mV[2] 
                    + mV[12]*other.mV[3];
    result.mV[1] = mV[1]*other.mV[0] + mV[5]*other.mV[1] + mV[9]*other.mV[2] 
                    + mV[13]*other.mV[3];
    result.mV[2] = mV[2]*other.mV[0] + mV[6]*other.mV[1] + mV[10]*other.mV[2] 
                    + mV[14]*other.mV[3];
    result.mV[3] = mV[3]*other.mV[0] + mV[7]*other.mV[1] + mV[11]*other.mV[2] 
                    + mV[15]*other.mV[3];

    result.mV[4] = mV[0]*other.mV[4] + mV[4]*other.mV[5] + mV[8]*other.mV[6] 
                    + mV[12]*other.mV[7];
    result.mV[5] = mV[1]*other.mV[4] + mV[5]*other.mV[5] + mV[9]*other.mV[6] 
                    + mV[13]*other.mV[7];
    result.mV[6] = mV[2]*other.mV[4] + mV[6]*other.mV[5] + mV[10]*other.mV[6] 
                    + mV[14]*other.mV[7];
    result.mV[7] = mV[3]*other.mV[4] + mV[7]*other.mV[5] + mV[11]*other.mV[6] 
                    + mV[15]*other.mV[7];

    result.mV[8] = mV[0]*other.mV[8] + mV[4]*other.mV[9] + mV[8]*other.mV[10] 
                    + mV[12]*other.mV[11];
    result.mV[9] = mV[1]*other.mV[8] + mV[5]*other.mV[9] + mV[9]*other.mV[10] 
                    + mV[13]*other.mV[11];
    result.mV[10] = mV[2]*other.mV[8] + mV[6]*other.mV[9] + mV[10]*other.mV[10] 
                    + mV[14]*other.mV[11];
    result.mV[11] = mV[3]*other.mV[8] + mV[7]*other.mV[9] + mV[11]*other.mV[10] 
                    + mV[15]*other.mV[11];

    result.mV[12] = mV[0]*other.mV[12] + mV[4]*other.mV[13] + mV[8]*other.mV[14] 
                    + mV[12]*other.mV[15];
    result.mV[13] = mV[1]*other.mV[12] + mV[5]*other.mV[13] + mV[9]*other.mV[14] 
                    + mV[13]*other.mV[15];
    result.mV[14] = mV[2]*other.mV[12] + mV[6]*other.mV[13] + mV[10]*other.mV[14] 
                    + mV[14]*other.mV[15];
    result.mV[15] = mV[3]*other.mV[12] + mV[7]*other.mV[13] + mV[11]*other.mV[14] 
                    + mV[15]*other.mV[15];

    for (unsigned int i = 0; i < 16; ++i)
    {
        mV[i] = result.mV[i];
    }

    return *this;

}   // End of Matrix44::operator*=()


//-------------------------------------------------------------------------------
// @ Matrix44::operator*()
//-------------------------------------------------------------------------------
// Matrix-column vector multiplication
//-------------------------------------------------------------------------------
Vector4   
Matrix44::operator*( const Vector4& other ) const
{
    Vector4 result;

    result.x = mV[0]*other.x + mV[4]*other.y + mV[8]*other.z + mV[12]*other.w;
    result.y = mV[1]*other.x + mV[5]*other.y + mV[9]*other.z + mV[13]*other.w;
    result.z = mV[2]*other.x + mV[6]*other.y + mV[10]*other.z + mV[14]*other.w;
    result.w = mV[3]*other.x + mV[7]*other.y + mV[11]*other.z + mV[15]*other.w;

    return result;

}   // End of Matrix44::operator*()


//-------------------------------------------------------------------------------
// @ ::operator*()
//-------------------------------------------------------------------------------
// Matrix-row vector multiplication
//-------------------------------------------------------------------------------
Vector4 
operator*( const Vector4& vector, const Matrix44& matrix )
{
    Vector4 result;

    result.x = matrix.mV[0]*vector.x + matrix.mV[1]*vector.y 
             + matrix.mV[2]*vector.z + matrix.mV[3]*vector.w;
    result.y = matrix.mV[4]*vector.x + matrix.mV[5]*vector.y 
             + matrix.mV[6]*vector.z + matrix.mV[7]*vector.w;
    result.z = matrix.mV[8]*vector.x + matrix.mV[9]*vector.y 
             + matrix.mV[10]*vector.z + matrix.mV[11]*vector.w;
    result.w = matrix.mV[12]*vector.x + matrix.mV[13]*vector.y 
             + matrix.mV[14]*vector.z + matrix.mV[15]*vector.w;

    return result;

}   // End of Matrix44::operator*()


//-------------------------------------------------------------------------------
// @ Matrix44::*=()
//-------------------------------------------------------------------------------
// Matrix-scalar multiplication
//-------------------------------------------------------------------------------
Matrix44& Matrix44::operator*=( float scalar )
{
    mV[0] *= scalar;
    mV[1] *= scalar;
    mV[2] *= scalar;
    mV[3] *= scalar;
    mV[4] *= scalar;
    mV[5] *= scalar;
    mV[6] *= scalar;
    mV[7] *= scalar;
    mV[8] *= scalar;
    mV[9] *= scalar;
    mV[10] *= scalar;
    mV[11] *= scalar;
    mV[12] *= scalar;
    mV[13] *= scalar;
    mV[14] *= scalar;
    mV[15] *= scalar;

    return *this;
}  // End of Matrix44::operator*=()


//-------------------------------------------------------------------------------
// @ friend Matrix44 *()
//-------------------------------------------------------------------------------
// Matrix-scalar multiplication
//-------------------------------------------------------------------------------
Matrix44 operator*( float scalar, const Matrix44& matrix )
{
    Matrix44 result;
    result.mV[0] = matrix.mV[0] * scalar;
    result.mV[1] = matrix.mV[1] * scalar;
    result.mV[2] = matrix.mV[2] * scalar;
    result.mV[3] = matrix.mV[3] * scalar;
    result.mV[4] = matrix.mV[4] * scalar;
    result.mV[5] = matrix.mV[5] * scalar;
    result.mV[6] = matrix.mV[6] * scalar;
    result.mV[7] = matrix.mV[7] * scalar;
    result.mV[8] = matrix.mV[8] * scalar;
    result.mV[9] = matrix.mV[9] * scalar;
    result.mV[10] = matrix.mV[10] * scalar;
    result.mV[11] = matrix.mV[11] * scalar;
    result.mV[12] = matrix.mV[12] * scalar;
    result.mV[13] = matrix.mV[13] * scalar;
    result.mV[14] = matrix.mV[14] * scalar;
    result.mV[15] = matrix.mV[15] * scalar;

    return result;
}  // End of friend Matrix44 operator*()


//-------------------------------------------------------------------------------
// @ Matrix44::*()
//-------------------------------------------------------------------------------
// Matrix-scalar multiplication
//-------------------------------------------------------------------------------
Matrix44 Matrix44::operator*( float scalar ) const
{
    Matrix44 result;
    result.mV[0] = mV[0] * scalar;
    result.mV[1] = mV[1] * scalar;
    result.mV[2] = mV[2] * scalar;
    result.mV[3] = mV[3] * scalar;
    result.mV[4] = mV[4] * scalar;
    result.mV[5] = mV[5] * scalar;
    result.mV[6] = mV[6] * scalar;
    result.mV[7] = mV[7] * scalar;
    result.mV[8] = mV[8] * scalar;
    result.mV[9] = mV[9] * scalar;
    result.mV[10] = mV[10] * scalar;
    result.mV[11] = mV[11] * scalar;
    result.mV[12] = mV[12] * scalar;
    result.mV[13] = mV[13] * scalar;
    result.mV[14] = mV[14] * scalar;
    result.mV[15] = mV[15] * scalar;

    return result;
}  // End of Matrix44::operator*=()


//-------------------------------------------------------------------------------
// @ Matrix44::Transform()
//-------------------------------------------------------------------------------
// Matrix-point multiplication
//-------------------------------------------------------------------------------
Vector3   
Matrix44::Transform( const Vector3& other ) const
{
    Vector3 result;

    result.x = mV[0]*other.x + mV[4]*other.y + mV[8]*other.z + mV[12];
    result.y = mV[1]*other.x + mV[5]*other.y + mV[9]*other.z + mV[13];
    result.z = mV[2]*other.x + mV[6]*other.y + mV[10]*other.z + mV[14];
 
    return result;

}   // End of Matrix44::Transform()


//-------------------------------------------------------------------------------
// @ Matrix44::TransformPoint()
//-------------------------------------------------------------------------------
// Matrix-point multiplication
//-------------------------------------------------------------------------------
Vector3   
Matrix44::TransformPoint( const Vector3& other ) const
{
    Vector3 result;

    result.x = mV[0]*other.x + mV[4]*other.y + mV[8]*other.z + mV[12];
    result.y = mV[1]*other.x + mV[5]*other.y + mV[9]*other.z + mV[13];
    result.z = mV[2]*other.x + mV[6]*other.y + mV[10]*other.z + mV[14];
 
    return result;

}   // End of Matrix44::TransformPoint()

} // namespace gfx
