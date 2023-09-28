#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Pulse::Layers::Camera {
    
    class ICameraTypeStrategy; // forward declaration of the camera type strategy interface to allow the camera module to use the interface without including the header file

} // namespace Pulse::Layers::Camera

namespace Pulse::Layers::Camera {

    // Use the setters without worrying about the recalculation of the matrices.
    // Its done automatically for you.
    // The Vectors and Quaternions are returned as const references to avoid copying.
    // The Direction Vectors are normalized and can be set too.

    // Type of the camera
    enum class Type {
        None = 0,
        Perspective,
        Orthographic,
        Isometric
    }; // enum Type

    // Base struct for camera data.
    struct CameraData {
        CameraData(Type cameraType, ICameraTypeStrategy* iCameraTypeStrategy, float nearPlane, float farPlane, const glm::vec3& position);

        virtual ~CameraData(); // virtual destructor to allow proper cleanup of derived classes. This deletes the camera type strategy.

        // Getters:
        Type GetCameraType() const;
        float GetNearPlane() const;
		float GetFarPlane() const;
        const glm::vec3& GetPosition() const;
        const glm::mat4& GetViewMatrix() const;
        const glm::mat4& GetProjectionMatrix() const;
        const glm::mat4& GetViewProjectionMatrix() const;

        // Setters:
		void SetNearPlane(float value);
        void SetFarPlane(float value);
		void SetPosition(const glm::vec3& value);

    protected:
        // Methods:
		void RecalculateViewMatrix();
		void RecalculateProjectionMatrix();
		void RecalculateViewProjectionMatrix();

    private:
        // Data:
        Type cameraType_ = Type::None;
        float nearPlane_ = 0.1f;
        float farPlane_ = 100.0f;
        glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::mat4 viewMatrix_ = glm::mat4(1.0f);
        glm::mat4 projectionMatrix_ = glm::mat4(1.0f);
        glm::mat4 viewProjectionMatrix_ = glm::mat4(1.0f);

        ICameraTypeStrategy* iCameraTypeStrategy_; // pointer to the camera type strategy interface to allow the camera module to use the interface without including the header file

        friend class PerspectiveCameraTypeStrategy; // friend class to allow the camera type strategies to access the camera module for faster access to the camera module
        friend class OrthographicCameraTypeStrategy; // friend class to allow the camera type strategies to access the camera module for faster access to the camera module
        friend class IsometricCameraTypeStrategy; // friend class to allow the camera type strategies to access the camera module for faster access to the camera module
    }; // struct CameraData

    // Struct to hold perspective camera data
    struct PerspectiveCameraData : public CameraData {
        PerspectiveCameraData(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::quat& rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
            float fieldOfView = 45.0f, float aspectRatio = 1.778f, float nearPlane = 0.1f, float farPlane = 100.0f);

        // Getters:
        float GetFieldOfView() const;
        float GetAspectRatio() const;
        const glm::vec3& GetFrontVec() const;
        const glm::vec3& GetUpVec() const;
        const glm::vec3& GetRightVec() const;
        const glm::quat& GetRotation() const;

        // Setters:
        void SetFieldOfView(float value);
        void SetAspectRatio(float value);
        void SetFrontVec(const glm::vec3& value);
        void SetUpVec(const glm::vec3& value);
        void SetRightVec(const glm::vec3& value);
        void SetRotation(const glm::quat& value);

    private:
        // Data:
        float fieldOfView_;
        float aspectRatio_;
        glm::vec3 frontVec_ = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 upVec_ = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 rightVec_ = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::quat rotation_ = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
        const float minFieldOfView_ = 0.0f;
        const float maxFieldOfView_ = 180.0f;

        friend class PerspectiveCameraTypeStrategy; // friend class to allow the camera type strategies to access the camera module for faster access to the camera module

    }; // struct PerspectiveCameraData

    // Now the Ortho struct in the same format as above:
    struct OrthographicCameraData : public CameraData {
        OrthographicCameraData(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), float zRotation = 0.0f, float left = -1.0f, float right = 1.0f, float bottom = -1.0f, float top = 1.0f,
            float nearPlane = 0.1f, float farPlane = 100.0f, float zoomLevel = 1.0f);

        // Getters: 
        float GetLeft() const;
        float GetRight() const;
        float GetBottom() const;
        float GetTop() const;
        const glm::vec3& GetUpVec() const;
        const glm::vec3& GetRightVec() const;
        float GetZRotation() const;
        float GetZoomLevel() const;

        // Setters:
        void SetLeft(float value);
        void SetRight(float value);
        void SetBottom(float value);
        void SetTop(float value);
        void SetUpVec(const glm::vec3& value);
        void SetRightVec(const glm::vec3& value);
        void SetZRotation(float value);
        void SetZoomLevel(float value);

    private:
        // Data:
        float left_;
        float right_;
        float bottom_;
        float top_;
        glm::vec3 upVec_ = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 rightVec_ = glm::vec3(1.0f, 0.0f, 0.0f);
        float zRotation_;
        float zoomLevel_;
        const float maxZoomLevel_ = 50000.0f;
        const float minZoomLevel_ = 0.001f;

        friend class OrthographicCameraTypeStrategy; // friend class to allow the camera type strategies to access the camera module for faster access to the camera module

    }; // struct OrthographicCameraData

    // Struct to hold isometric camera data
    struct IsometricCameraData : public CameraData {
        IsometricCameraData(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::quat& rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
            float left = -1.0f, float right = 1.0f, float bottom = -1.0f, float top = 1.0f,
            float nearPlane = 0.1f, float farPlane = 100.0f, float zoomLevel = 1.0f);

        // Getters:
        float GetLeft() const;
        float GetRight() const;
        float GetBottom() const;
        float GetTop() const;
        const glm::vec3& GetFrontVec() const;
        const glm::vec3& GetUpVec() const;
        const glm::vec3& GetRightVec() const;
        const glm::quat& GetRotation() const;
        float GetZoomLevel() const;

        // Setters:
        void SetLeft(float value);
        void SetRight(float value);
        void SetBottom(float value);
        void SetTop(float value);
        void SetFrontVec(const glm::vec3& value);
        void SetUpVec(const glm::vec3& value);
        void SetRightVec(const glm::vec3& value);
        void SetRotation(const glm::quat& value);
        void SetZoomLevel(float value);

    private:
        // Data:
        float left_;
        float right_;
        float bottom_;
        float top_;
        glm::vec3 frontVec_ = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 upVec_ = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 rightVec_ = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::quat rotation_ = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
        float zoomLevel_;
        const float maxZoomLevel_ = 50000.0f;
        const float minZoomLevel_ = 0.001f;

        friend class IsometricCameraTypeStrategy; // friend class to allow the camera type strategies to access the camera module for faster access to the camera module

    }; // struct IsometricCameraData

} // namespace Pulse::Layers::Camera
