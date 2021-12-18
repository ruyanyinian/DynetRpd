#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>
#include "dynet/globals.hpp"
#include "dynet/devices.hpp"
namespace dynet {
class ParameterCollection;

struct ParameterStorageBase {
    friend class ParameterCollection;
    /**
     * @brief 对参数进行scale
     * 
     * @param a scale factor
     */
    virtual void scale_parameters(float a) = 0;
    /**
     * @brief 对gradient进行scale
     * 
     * @param a scale factor
     */
    virtual void scale_gradient(float a) = 0;
    /**
     * @brief 把参数设置成0
     */
    virtual void zero() = 0;
    virtual ~ParameterStorageBase() {};
}; // struct ParameterStorageBase

struct ParameterStorage : public ParameterStorageBase {
    //默认public
    friend class ParameterCollection;
    template <class MyDevice>
    void scale_parameters_dev(MyDevice& dev, float a);
    void scale_parameters(float a) override;
    template <class MyDevice>
    void scale_gradient_dev(MyDevice & dev, float a);
    void scale_gradient(float a) override;
    void zero() override;

    std::string name; /*< Name of this parameter*/
    Dim dim; /**< Dimensions of the parameter tensor*/
    Tensor values; /**< value of the parameter*/
    Tensor g;  /**< Values of the gradient w.r.t. this parameter */
    bool updated; /**< Whether this is updated */
    bool nonzero_grad ; /**< Whether the gradient is zero */
    ParameterCollection* owner; /**< Pointer to the collection that "owns" this parameter */
    Device* device; 
    // protected
protected:
    ParameterStorage() : updated(true), owner(nullptr) {}
    explicit ParameterStorage(const Dim& d, float scale,
                            const std::string & name, Device *device); // initialize with a scale
    explicit ParameterStorage(const Dim& d, const ParameterInit & init,
                            const std::string & name, Device *device); // initialize with custom initializer  
    
};
struct Parameter {
    Parameter();
    std::string get_fullname() const;
    void set_value(const std::vector<float>& value);
};
} /*dynet*/
#endif /*MODEL_HPP*/