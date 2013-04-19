#ifndef MONGO_BASE_CONTEXT_HPP_INCLUDED
#define MONGO_BASE_CONTEXT_HPP_INCLUDED



namespace mongo {

class context {
    MONGO_DECLARE_NONCOPYABLE(context)

    public:
        context(config_t config, const std::string& logger);
        context(config_t config, std::unique_ptr<logging::logger_concept_t>&& logger);
       ~context();

        // Component API

        template<class Category, typename... Args>
        typename api::category_traits<Category>::ptr_type
        get(const std::string& type, Args&&... args);

        // Logging

        logging::logger_concept_t&
        logger() {
            return *m_logger;
        }

    private:
        void
        bootstrap();

    private:
};
} // namespace mongo
#endif // MONGO_BASE_CONTEXT_HPP_INCLUDED
