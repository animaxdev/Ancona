#ifndef Ancona_Engine_Loading_PolymorphicRegistration_H_
#define Ancona_Engine_Loading_PolymorphicRegistration_H_

#include <string>

#include <Ancona/Engine/Loading/Archive.hpp>
#include <Ancona/Engine/Loading/ClassConstructor.hpp>
#include <Ancona/Engine/Loading/PolymorphicSerializer.hpp>
#include <Ancona/Util/Assert.hpp>

#define REGISTER_POLYMORPHIC_SERIALIZER(CLASS)                           \
    template<> const std::string ild::PolymorphicTypeKey<CLASS>::Key =   \
        PolymorphicRegistration::RegisterType<CLASS>(#CLASS);

#define REGISTER_POLYMORPHIC_SERIALIZER_ABSTRACT_BASE(CLASS)             \
    template <> const std::string ild::PolymorphicTypeKey<CLASS>::Key =  \
        PolymorphicRegistration::RegisterAbstractType<CLASS>(#CLASS);


namespace ild
{

template <class T>
class PolymorphicSerializerImpl : public PolymorphicSerializer
{
    public:

        /**
         * @copydoc ild::PolymorphicSerializer::Serialize()
         */
        void Serialize(void *& property, Archive & arc) override
        {
            T *& typedProp = (T *&)(property);
            if(arc.IsLoading())
            {
                typedProp = new T();
            }
            Serializer<T>::Serialize(*typedProp, arc);
        }
};

/**
 * @brief Used to provide a map entry for abstract bases of polymorphic types.
 * @author Jeff Swenson
 */
class PolymorphicSerializerAbstractBase : public PolymorphicSerializer
{
    public:
         PolymorphicSerializerAbstractBase(std::string className);
        /**
         * @copydoc ild::PolymorphicSerializer::Serialize()
         */
        void Serialize(void *& property, Archive & arc) override;
    private:
        std::string _className;

};


namespace PolymorphicRegistration
{
    /**
     * @brief Saves a mapping between the string name and the type.
     *
     * @tparam T Type being registered
     * @param name Name representing the type.
     *
     * @return The name representing the type.
     */
    template <class T>
    std::string static RegisterType(const std::string & name)
    {
        PolymorphicMap::RegisterType(
                name,
                std::type_index(typeid(T)),
                new PolymorphicSerializerImpl<T>()
                );
        return name;
    }

    /**
     * @brief Saves a mapping between the string name and an abstract type type.
     *
     * @tparam T Type being registered
     * @param name Name representing the type.
     *
     * @return The name representing the type.
     */
    template <class T>
    std::string static RegisterAbstractType(const std::string & name)
    {
        PolymorphicMap::RegisterType(
                name,
                std::type_index(typeid(T)),
                new PolymorphicSerializerAbstractBase(name)
        );
        return name;
    }
}


}


#endif 
