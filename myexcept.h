#pragma once
#include <list>
#include <sstream>

/**
 * @brief All myexcept components are located in here
 */
namespace myexcept{

    /**
     * @brief Handles exceptions
     */
    class myexcept
    {
    private:
        /**
         * @brief holds function name and what went wrong from its perspective.
         */
        struct call
        {
            /**
             * @brief function name.
             */
            const char* pos;
            /**
             * @brief description what went wrong from functions perspective.
             */
            const char* desc;
        };
        /**
         * @brief list of calls collected when catched.
         */
        std::list<call> callstack;
        
    public:
        myexcept() = delete;
        /**
         * @brief Construct a new myexcept object
         */
        myexcept(const char* pos, const char* desc){
            pack(pos, desc);
        };
        /**
         * @brief adds call specific information to the callstack for later tracing.
         * @param pos function name
         * @param desc description of what went wrong
         */
        void pack(const char* pos, const char* desc){
            callstack.push_front(call{pos, desc});
        };

        std::string get() const noexcept {
            std::stringstream ss;
            ss <<       "Exception occured. Please check the following callstack:\n";
            for(const call& c : callstack){
                ss <<   "    ... in " << c.pos << " - " << c.desc << " .-\n";
            }

            ss <<       "    ... end of callstack\n";
            return ss.str();
        };

        /**
         * @brief Converts exception to string
         * @return const char* 
         */
        inline operator std::string () const noexcept {
            return get();
        };
        
        /**
         * @brief calls pack function
         */
        inline void operator()(const char* pos, const char* desc) { pack(pos, desc); };
    };

}