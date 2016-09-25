#include "Matrix4x4.hpp"
#include <cassert>

namespace FishEngine {

    Matrix4x4 Matrix4x4::Inverse(const Matrix4x4& m)
    {
        //return glm::inverse((glm::mat4)m);
        float p10_21 = m.m[1][0] * m.m[2][1] - m.m[2][0] * m.m[1][1];
        float p10_22 = m.m[1][0] * m.m[2][2] - m.m[2][0] * m.m[1][2];
        float p10_23 = m.m[1][0] * m.m[2][3] - m.m[2][0] * m.m[1][3];
        float p11_22 = m.m[1][1] * m.m[2][2] - m.m[2][1] * m.m[1][2];
        float p11_23 = m.m[1][1] * m.m[2][3] - m.m[2][1] * m.m[1][3];
        float p12_23 = m.m[1][2] * m.m[2][3] - m.m[2][2] * m.m[1][3];
        float p10_31 = m.m[1][0] * m.m[3][1] - m.m[3][0] * m.m[1][1];
        float p10_32 = m.m[1][0] * m.m[3][2] - m.m[3][0] * m.m[1][2];
        float p10_33 = m.m[1][0] * m.m[3][3] - m.m[3][0] * m.m[1][3];
        float p11_32 = m.m[1][1] * m.m[3][2] - m.m[3][1] * m.m[1][2];
        float p11_33 = m.m[1][1] * m.m[3][3] - m.m[3][1] * m.m[1][3];
        float p12_33 = m.m[1][2] * m.m[3][3] - m.m[3][2] * m.m[1][3];
        float p20_31 = m.m[2][0] * m.m[3][1] - m.m[3][0] * m.m[2][1];
        float p20_32 = m.m[2][0] * m.m[3][2] - m.m[3][0] * m.m[2][2];
        float p20_33 = m.m[2][0] * m.m[3][3] - m.m[3][0] * m.m[2][3];
        float p21_32 = m.m[2][1] * m.m[3][2] - m.m[3][1] * m.m[2][2];
        float p21_33 = m.m[2][1] * m.m[3][3] - m.m[3][1] * m.m[2][3];
        float p22_33 = m.m[2][2] * m.m[3][3] - m.m[3][2] * m.m[2][3];
        Matrix4x4 A;
        A.m[0][0] = +(m.m[1][1] * p22_33 - m.m[1][2] * p21_33 + m.m[1][3] * p21_32);
        A.m[1][0] = -(m.m[1][0] * p22_33 - m.m[1][2] * p20_33 + m.m[1][3] * p20_32);
        A.m[2][0] = +(m.m[1][0] * p21_33 - m.m[1][1] * p20_33 + m.m[1][3] * p20_31);
        A.m[3][0] = -(m.m[1][0] * p21_32 - m.m[1][1] * p20_32 + m.m[1][2] * p20_31);
        A.m[0][1] = -(m.m[0][1] * p22_33 - m.m[0][2] * p21_33 + m.m[0][3] * p21_32);
        A.m[1][1] = +(m.m[0][0] * p22_33 - m.m[0][2] * p20_33 + m.m[0][3] * p20_32);
        A.m[2][1] = -(m.m[0][0] * p21_33 - m.m[0][1] * p20_33 + m.m[0][3] * p20_31);
        A.m[3][1] = +(m.m[0][0] * p21_32 - m.m[0][1] * p20_32 + m.m[0][2] * p20_31);
        A.m[0][2] = +(m.m[0][1] * p12_33 - m.m[0][2] * p11_33 + m.m[0][3] * p11_32);
        A.m[1][2] = -(m.m[0][0] * p12_33 - m.m[0][2] * p10_33 + m.m[0][3] * p10_32);
        A.m[2][2] = +(m.m[0][0] * p11_33 - m.m[0][1] * p10_33 + m.m[0][3] * p10_31);
        A.m[3][2] = -(m.m[0][0] * p11_32 - m.m[0][1] * p10_32 + m.m[0][2] * p10_31);
        A.m[0][3] = -(m.m[0][1] * p12_23 - m.m[0][2] * p11_23 + m.m[0][3] * p11_22);
        A.m[1][3] = +(m.m[0][0] * p12_23 - m.m[0][2] * p10_23 + m.m[0][3] * p10_22);
        A.m[2][3] = -(m.m[0][0] * p11_23 - m.m[0][1] * p10_23 + m.m[0][3] * p10_21);
        A.m[3][3] = +(m.m[0][0] * p11_22 - m.m[0][1] * p10_22 + m.m[0][2] * p10_21);

        float det = 0;
        det += m.m[0][0] * A.m[0][0];
        det += m.m[0][1] * A.m[1][0];
        det += m.m[0][2] * A.m[2][0];
        det += m.m[0][3] * A.m[3][0];
        float inv_det = 1.f / det;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                A.m[i][j] *= inv_det;
            }
        }

        auto I = A*m;
        if (!I.isIdentity()) {
            abort();
        }
        return A;
    }

    bool Zero(float f) {
        return (f < 1e-4f) && (f > -1e-4f);
    }
    
    bool One(float f) {
        return (f-1 < 1e-4f) && (f-1 > -1e-4f);
    }
    
    bool Matrix4x4::isIdentity() const
    {
        return
        One(m[0][0]) && Zero(m[0][1]) && Zero(m[0][2]) && Zero(m[0][3]) &&
        Zero(m[1][0]) && One(m[1][1]) && Zero(m[1][2]) && Zero(m[1][3]) &&
        Zero(m[2][0]) && Zero(m[2][1]) && One(m[2][2]) && Zero(m[2][3]) &&
        Zero(m[3][0]) && Zero(m[3][1]) && Zero(m[3][2]) && One(m[3][3]);
    }
    
    //Matrix4x4 translate(const Matrix4x4& m, float tx, float ty, float tz)
    //{
    //    Matrix4x4 result = m;
    //    Vector4 col3(tx, ty, tz, 1.f);
    //    result.m[0][3] = Vector4::Dot(m.rows[0], col3);
    //    result.m[1][3] = Vector4::Dot(m.rows[1], col3);
    //    result.m[2][3] = Vector4::Dot(m.rows[2], col3);
    //    result.m[3][3] = Vector4::Dot(m.rows[3], col3);
    //    return result;
    //}

    void Matrix4x4::SetTRS(const Vector3& pos, const Quaternion& q, const Vector3& s)
    {
        //*this = glm::scale(glm::translate(glm::mat4(1.0f), (glm::vec3)pos) * glm::mat4_cast((glm::quat)q), (glm::vec3)s);
        //*this = glm::translate(glm::mat4(1.0f), (glm::vec3)pos) * glm::mat4_cast((glm::quat)q) * glm::scale(glm::mat4(1.0f), (glm::vec3)s);
        //*this = glm::mat4_cast((glm::quat)q);
        *this = Matrix4x4::FromRotation(q);

        m[0][3] = pos.x;
        m[1][3] = pos.y;
        m[2][3] = pos.z;
        m[0][0] *= s.x;
        m[0][1] *= s.y;
        m[0][2] *= s.z;
        m[1][0] *= s.x;
        m[1][1] *= s.y;
        m[1][2] *= s.z;
        m[2][0] *= s.x;
        m[2][1] *= s.y;
        m[2][2] *= s.z;
        m[3][3] = 1.f;
    }

    void Matrix4x4::TRS(
        const Vector3&      translation,
        const Quaternion&   rotation,
        const Vector3&      scale,
        Matrix4x4&          outLocalToWorld, 
        Matrix4x4&          outWorldToLocal)
    {
        // outLocalToWorld = TRS
        // outWorldToLocal = inverse(outLocalToWorld) = (S^-1)(R')(T^-1)
        //outLocalToWorld = glm::mat4_cast((glm::quat)rotation);
        outLocalToWorld = Matrix4x4::FromRotation(rotation);
        
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                outWorldToLocal.m[i][j] = outLocalToWorld.m[j][i];
            }
        }

        outLocalToWorld.m[0][3] = translation.x;
        outLocalToWorld.m[1][3] = translation.y;
        outLocalToWorld.m[2][3] = translation.z;
        
        Vector4 col3(-translation.x, -translation.y, -translation.z, 0); // use 0 instead 1, since we have not yet cleared the last column of outWorldToLocal.
        float m03 = Vector4::Dot(outWorldToLocal.rows[0], col3);
        float m13 = Vector4::Dot(outWorldToLocal.rows[1], col3);
        float m23 = Vector4::Dot(outWorldToLocal.rows[2], col3);
        outWorldToLocal.m[0][3] = m03;
        outWorldToLocal.m[1][3] = m13;
        outWorldToLocal.m[2][3] = m23;

        outLocalToWorld.m[0][0] *= scale.x;
        outLocalToWorld.m[0][1] *= scale.y;
        outLocalToWorld.m[0][2] *= scale.z;
        outLocalToWorld.m[1][0] *= scale.x;
        outLocalToWorld.m[1][1] *= scale.y;
        outLocalToWorld.m[1][2] *= scale.z;
        outLocalToWorld.m[2][0] *= scale.x;
        outLocalToWorld.m[2][1] *= scale.y;
        outLocalToWorld.m[2][2] *= scale.z;

        float inv_sx = 1.0f / scale.x;
        float inv_sy = 1.0f / scale.y;
        float inv_sz = 1.0f / scale.z;
        outWorldToLocal.m[0][0] *= inv_sx;
        outWorldToLocal.m[0][1] *= inv_sx;
        outWorldToLocal.m[0][2] *= inv_sx;
        outWorldToLocal.m[1][0] *= inv_sy;
        outWorldToLocal.m[1][1] *= inv_sy;
        outWorldToLocal.m[1][2] *= inv_sy;
        outWorldToLocal.m[2][0] *= inv_sz;
        outWorldToLocal.m[2][1] *= inv_sz;
        outWorldToLocal.m[2][2] *= inv_sz;

        outLocalToWorld.m[3][3] = 1.f;
        outWorldToLocal.m[3][3] = 1.f;

        // TODO: remove later
        //auto test = outWorldToLocal * outLocalToWorld;
        //if (!test.isIdentity()) {
        //    Assert(false);
        //}
    }

    Quaternion Matrix4x4::ToRotation() const
    {
        //return glm::quat_cast((glm::mat4)*this);
        float fourXSquaredMinus1 = m[0][0] - m[1][1] - m[2][2];
        float fourYSquaredMinus1 = m[1][1] - m[0][0] - m[2][2];
        float fourZSquaredMinus1 = m[2][2] - m[0][0] - m[1][1];
        float fourWSquaredMinus1 = m[0][0] + m[1][1] + m[2][2];

        int biggestIndex = 0;
        float fourBiggestSquaredMinus1 = fourWSquaredMinus1;
        if (fourXSquaredMinus1 > fourBiggestSquaredMinus1)
        {
            fourBiggestSquaredMinus1 = fourXSquaredMinus1;
            biggestIndex = 1;
        }
        if (fourYSquaredMinus1 > fourBiggestSquaredMinus1)
        {
            fourBiggestSquaredMinus1 = fourYSquaredMinus1;
            biggestIndex = 2;
        }
        if (fourZSquaredMinus1 > fourBiggestSquaredMinus1)
        {
            fourBiggestSquaredMinus1 = fourZSquaredMinus1;
            biggestIndex = 3;
        }

        float biggestVal = sqrtf(fourBiggestSquaredMinus1 + 1.f) * 0.5f;
        float mult = 0.25f / biggestVal;

        Quaternion result;
        switch (biggestIndex)
        {
        case 0:
            result.w = biggestVal;
            result.x = (m[2][1] - m[1][2]) * mult;
            result.y = (m[0][2] - m[2][0]) * mult;
            result.z = (m[1][0] - m[0][1]) * mult;
            break;
        case 1:
            result.w = (m[2][1] - m[1][2]) * mult;
            result.x = biggestVal;
            result.y = (m[1][0] + m[0][1]) * mult;
            result.z = (m[0][2] + m[2][0]) * mult;
            break;
        case 2:
            result.w = (m[0][2] - m[2][0]) * mult;
            result.x = (m[1][0] + m[0][1]) * mult;
            result.y = biggestVal;
            result.z = (m[2][1] + m[1][2]) * mult;
            break;
        case 3:
            result.w = (m[1][0] - m[0][1]) * mult;
            result.x = (m[0][2] + m[2][0]) * mult;
            result.y = (m[2][1] + m[1][2]) * mult;
            result.z = biggestVal;
            break;

        default:					// Silence a -Wswitch-default warning in GCC. Should never actually get here. Assert is just for sanity.
            assert(false);
            break;
        }
        return result;
    }
    
    Matrix4x4 Matrix4x4::FromRotation(const Quaternion& rotation)
    {
        // Real-time rendering 3rd, p76
        auto& q = rotation;
        //return glm::mat4_cast(glm::quat(r.w, r.x, r.y, r.z));
        Matrix4x4 result;
        float qxx = q.x * q.x;
        float qyy = q.y * q.y;
        float qzz = q.z * q.z;
        float qxz = q.x * q.z;
        float qxy = q.x * q.y;
        float qyz = q.y * q.z;
        float qwx = q.w * q.x;
        float qwy = q.w * q.y;
        float qwz = q.w * q.z;
        
        result.m[0][0] = 1.f - 2.f * (qyy + qzz);
        result.m[1][0] = 2.f * (qxy + qwz);
        result.m[2][0] = 2.f * (qxz - qwy);
        
        result.m[0][1] = 2.f * (qxy - qwz);
        result.m[1][1] = 1.f - 2.f * (qxx + qzz);
        result.m[2][1] = 2.f * (qyz + qwx);
        
        result.m[0][2] = 2.f * (qxz + qwy);
        result.m[1][2] = 2.f * (qyz - qwx);
        result.m[2][2] = 1.f - 2.f * (qxx + qyy);
        return result;
    }

    Matrix4x4 Matrix4x4::Perspective(float fovy, float aspect, float zNear, float zFar)
    {
        //return glm::perspectiveLH(glm::radians(fovy), aspect, zNear, zFar);
        assert(fabsf(aspect - std::numeric_limits<float>::epsilon()) > 0.f);

        float const tanHalfFovy = tan(Mathf::Radians(fovy) / 2.f);

        Matrix4x4 result;
        result.m[0][0] = 1.f / (aspect * tanHalfFovy);
        result.m[1][1] = 1.f / (tanHalfFovy);
        result.m[3][2] = 1.f;

//#		if GLM_DEPTH_CLIP_SPACE == GLM_DEPTH_ZERO_TO_ONE
//        result.m[2][2] = zFar / (zFar - zNear);
//        result.m[2][3] = -(zFar * zNear) / (zFar - zNear);
//#		else
        result.m[2][2] = (zFar + zNear) / (zFar - zNear);
        result.m[2][3] = -(2.f * zFar * zNear) / (zFar - zNear);
//#		endif

        return result;
    }

    FishEngine::Matrix4x4 Matrix4x4::Ortho(float left, float right, float bottom, float top, float zNear, float zFar)
    {
        //return glm::orthoLH(left, right, bottom, top, zNear, zFar);
        Matrix4x4 result;
        result.m[0][0] = 2.f / (right - left);
        result.m[1][1] = 2.f / (top - bottom);
        result.m[0][3] = -(right + left) / (right - left);
        result.m[1][3] = -(top + bottom) / (top - bottom);

//#		if GLM_DEPTH_CLIP_SPACE == GLM_DEPTH_ZERO_TO_ONE
//        result.m[2][2] = 1.f / (zFar - zNear);
//        result.m[2][3] = -zNear / (zFar - zNear);
//#		else
        result.m[2][2] = 2.f / (zFar - zNear);
        result.m[2][3] = -(zFar + zNear) / (zFar - zNear);
//#		endif

        return result;
    }

    Matrix4x4 Matrix4x4::LookAt(const Vector3& eye, const Vector3& center, const Vector3 up)
    {
        //return glm::lookAtLH(glm::vec3(eye), glm::vec3(center), glm::vec3(up));
        Vector3 f = Vector3::Normalize(center - eye);
        Vector3 s = Vector3::Normalize(Vector3::Cross(up, f));
        Vector3 u = Vector3::Cross(f, s);

        Matrix4x4 result;
        result.m[0][0] = s.x;
        result.m[0][1] = s.y;
        result.m[0][2] = s.z;
        result.m[1][0] = u.x;
        result.m[1][1] = u.y;
        result.m[1][2] = u.z;
        result.m[2][0] = f.x;
        result.m[2][1] = f.y;
        result.m[2][2] = f.z;
        result.m[0][3] = -Vector3::Dot(s, eye);
        result.m[1][3] = -Vector3::Dot(u, eye);
        result.m[2][3] = -Vector3::Dot(f, eye);
        return result;
    }

    const Matrix4x4 Matrix4x4::identity(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1);
    const Matrix4x4 Matrix4x4::zero(
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0);

}
