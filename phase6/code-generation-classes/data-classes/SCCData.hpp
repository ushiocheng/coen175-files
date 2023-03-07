#if !defined(SCC_DATA_HPP)
#define SCC_DATA_HPP

/**
 * (Dynamic) Data
 * Abstract representation of data
 * including variables and intermediate values
 */
class SCCData {
   private:
    /* data */
   public:
    SCCData(/* args */);
    ~SCCData();
    
    /**
     * Load this Data for access
    */
    virtual void load() = 0;
};

#endif  // SCC_DATA_HPP
