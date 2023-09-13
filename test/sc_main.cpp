//
// Main routine for SystemC.
// Initialize and run Googletest.
// This file should be included into every TLM test.
//
int sc_main(int argc, char *argv[])
{
    // Disable the Accellera copyright message.
    setenv("SYSTEMC_DISABLE_COPYRIGHT_MESSAGE", "1", 1);

    // SystemC time resolution set to 1 ns.
    sc_core::sc_set_time_resolution(1, sc_core::SC_NS);

    testing::InitGoogleTest(&argc, argv);
    int status = RUN_ALL_TESTS();

    return status;
}
