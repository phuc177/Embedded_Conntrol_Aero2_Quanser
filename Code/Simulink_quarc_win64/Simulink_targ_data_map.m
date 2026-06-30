    function targMap = targDataMap(),

    ;%***********************
    ;% Create Parameter Map *
    ;%***********************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 6;
        sectIdxOffset = 0;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc paramMap
        ;%
        paramMap.nSections           = nTotSects;
        paramMap.sectIdxOffset       = sectIdxOffset;
            paramMap.sections(nTotSects) = dumSection; %prealloc
        paramMap.nTotData            = -1;

        ;%
        ;% Auto data (Simulink_P)
        ;%
            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% Simulink_P.HILWriteAnalog_channels
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% Simulink_P.HILRead_other_channels
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 2;

            nTotData = nTotData + section.nData;
            paramMap.sections(1) = section;
            clear section

            section.nData     = 24;
            section.data(24)  = dumData; %prealloc

                    ;% Simulink_P.HILInitialize_OOTerminate
                    section.data(1).logicalSrcIdx = 2;
                    section.data(1).dtTransOffset = 0;

                    ;% Simulink_P.HILInitialize_OOExit
                    section.data(2).logicalSrcIdx = 3;
                    section.data(2).dtTransOffset = 1;

                    ;% Simulink_P.HILInitialize_OOStart
                    section.data(3).logicalSrcIdx = 4;
                    section.data(3).dtTransOffset = 2;

                    ;% Simulink_P.HILInitialize_OOEnter
                    section.data(4).logicalSrcIdx = 5;
                    section.data(4).dtTransOffset = 3;

                    ;% Simulink_P.HILInitialize_AOFinal
                    section.data(5).logicalSrcIdx = 6;
                    section.data(5).dtTransOffset = 4;

                    ;% Simulink_P.HILInitialize_OOFinal
                    section.data(6).logicalSrcIdx = 7;
                    section.data(6).dtTransOffset = 5;

                    ;% Simulink_P.HILInitialize_AIHigh
                    section.data(7).logicalSrcIdx = 8;
                    section.data(7).dtTransOffset = 8;

                    ;% Simulink_P.HILInitialize_AILow
                    section.data(8).logicalSrcIdx = 9;
                    section.data(8).dtTransOffset = 9;

                    ;% Simulink_P.HILInitialize_AOHigh
                    section.data(9).logicalSrcIdx = 10;
                    section.data(9).dtTransOffset = 10;

                    ;% Simulink_P.HILInitialize_AOLow
                    section.data(10).logicalSrcIdx = 11;
                    section.data(10).dtTransOffset = 11;

                    ;% Simulink_P.HILInitialize_AOInitial
                    section.data(11).logicalSrcIdx = 12;
                    section.data(11).dtTransOffset = 12;

                    ;% Simulink_P.HILInitialize_AOWatchdog
                    section.data(12).logicalSrcIdx = 13;
                    section.data(12).dtTransOffset = 13;

                    ;% Simulink_P.HILInitialize_OOInitial
                    section.data(13).logicalSrcIdx = 14;
                    section.data(13).dtTransOffset = 14;

                    ;% Simulink_P.HILInitialize_OOWatchdog
                    section.data(14).logicalSrcIdx = 15;
                    section.data(14).dtTransOffset = 17;

                    ;% Simulink_P.Constant_Value
                    section.data(15).logicalSrcIdx = 16;
                    section.data(15).dtTransOffset = 20;

                    ;% Simulink_P.Gain_Gain
                    section.data(16).logicalSrcIdx = 17;
                    section.data(16).dtTransOffset = 21;

                    ;% Simulink_P.Gain1_Gain
                    section.data(17).logicalSrcIdx = 18;
                    section.data(17).dtTransOffset = 22;

                    ;% Simulink_P.DerivLPF_A
                    section.data(18).logicalSrcIdx = 19;
                    section.data(18).dtTransOffset = 23;

                    ;% Simulink_P.DerivLPF_C
                    section.data(19).logicalSrcIdx = 20;
                    section.data(19).dtTransOffset = 24;

                    ;% Simulink_P.DerivLPF_D
                    section.data(20).logicalSrcIdx = 21;
                    section.data(20).dtTransOffset = 25;

                    ;% Simulink_P.LPF_A
                    section.data(21).logicalSrcIdx = 22;
                    section.data(21).dtTransOffset = 26;

                    ;% Simulink_P.LPF_C
                    section.data(22).logicalSrcIdx = 23;
                    section.data(22).dtTransOffset = 27;

                    ;% Simulink_P.Gain3_Gain
                    section.data(23).logicalSrcIdx = 24;
                    section.data(23).dtTransOffset = 28;

                    ;% Simulink_P.Gain2_Gain
                    section.data(24).logicalSrcIdx = 25;
                    section.data(24).dtTransOffset = 29;

            nTotData = nTotData + section.nData;
            paramMap.sections(2) = section;
            clear section

            section.nData     = 4;
            section.data(4)  = dumData; %prealloc

                    ;% Simulink_P.HILInitialize_CKChannels
                    section.data(1).logicalSrcIdx = 26;
                    section.data(1).dtTransOffset = 0;

                    ;% Simulink_P.HILInitialize_DOWatchdog
                    section.data(2).logicalSrcIdx = 27;
                    section.data(2).dtTransOffset = 1;

                    ;% Simulink_P.HILInitialize_EIInitial
                    section.data(3).logicalSrcIdx = 28;
                    section.data(3).dtTransOffset = 2;

                    ;% Simulink_P.HILReadEncoderTimebase_Clock
                    section.data(4).logicalSrcIdx = 29;
                    section.data(4).dtTransOffset = 3;

            nTotData = nTotData + section.nData;
            paramMap.sections(3) = section;
            clear section

            section.nData     = 8;
            section.data(8)  = dumData; %prealloc

                    ;% Simulink_P.HILInitialize_AIChannels
                    section.data(1).logicalSrcIdx = 30;
                    section.data(1).dtTransOffset = 0;

                    ;% Simulink_P.HILInitialize_AOChannels
                    section.data(2).logicalSrcIdx = 31;
                    section.data(2).dtTransOffset = 2;

                    ;% Simulink_P.HILInitialize_DOChannels
                    section.data(3).logicalSrcIdx = 32;
                    section.data(3).dtTransOffset = 4;

                    ;% Simulink_P.HILInitialize_EIChannels
                    section.data(4).logicalSrcIdx = 33;
                    section.data(4).dtTransOffset = 6;

                    ;% Simulink_P.HILInitialize_EIQuadrature
                    section.data(5).logicalSrcIdx = 34;
                    section.data(5).dtTransOffset = 10;

                    ;% Simulink_P.HILInitialize_OOChannels
                    section.data(6).logicalSrcIdx = 35;
                    section.data(6).dtTransOffset = 11;

                    ;% Simulink_P.HILReadEncoderTimebase_Channels
                    section.data(7).logicalSrcIdx = 36;
                    section.data(7).dtTransOffset = 14;

                    ;% Simulink_P.HILReadEncoderTimebase_SamplesI
                    section.data(8).logicalSrcIdx = 37;
                    section.data(8).dtTransOffset = 15;

            nTotData = nTotData + section.nData;
            paramMap.sections(4) = section;
            clear section

            section.nData     = 38;
            section.data(38)  = dumData; %prealloc

                    ;% Simulink_P.HILInitialize_Active
                    section.data(1).logicalSrcIdx = 38;
                    section.data(1).dtTransOffset = 0;

                    ;% Simulink_P.HILInitialize_AOTerminate
                    section.data(2).logicalSrcIdx = 39;
                    section.data(2).dtTransOffset = 1;

                    ;% Simulink_P.HILInitialize_AOExit
                    section.data(3).logicalSrcIdx = 40;
                    section.data(3).dtTransOffset = 2;

                    ;% Simulink_P.HILInitialize_DOTerminate
                    section.data(4).logicalSrcIdx = 41;
                    section.data(4).dtTransOffset = 3;

                    ;% Simulink_P.HILInitialize_DOExit
                    section.data(5).logicalSrcIdx = 42;
                    section.data(5).dtTransOffset = 4;

                    ;% Simulink_P.HILInitialize_POTerminate
                    section.data(6).logicalSrcIdx = 43;
                    section.data(6).dtTransOffset = 5;

                    ;% Simulink_P.HILInitialize_POExit
                    section.data(7).logicalSrcIdx = 44;
                    section.data(7).dtTransOffset = 6;

                    ;% Simulink_P.HILInitialize_CKPStart
                    section.data(8).logicalSrcIdx = 45;
                    section.data(8).dtTransOffset = 7;

                    ;% Simulink_P.HILInitialize_CKPEnter
                    section.data(9).logicalSrcIdx = 46;
                    section.data(9).dtTransOffset = 8;

                    ;% Simulink_P.HILInitialize_CKStart
                    section.data(10).logicalSrcIdx = 47;
                    section.data(10).dtTransOffset = 9;

                    ;% Simulink_P.HILInitialize_CKEnter
                    section.data(11).logicalSrcIdx = 48;
                    section.data(11).dtTransOffset = 10;

                    ;% Simulink_P.HILInitialize_AIPStart
                    section.data(12).logicalSrcIdx = 49;
                    section.data(12).dtTransOffset = 11;

                    ;% Simulink_P.HILInitialize_AIPEnter
                    section.data(13).logicalSrcIdx = 50;
                    section.data(13).dtTransOffset = 12;

                    ;% Simulink_P.HILInitialize_AOPStart
                    section.data(14).logicalSrcIdx = 51;
                    section.data(14).dtTransOffset = 13;

                    ;% Simulink_P.HILInitialize_AOPEnter
                    section.data(15).logicalSrcIdx = 52;
                    section.data(15).dtTransOffset = 14;

                    ;% Simulink_P.HILInitialize_AOStart
                    section.data(16).logicalSrcIdx = 53;
                    section.data(16).dtTransOffset = 15;

                    ;% Simulink_P.HILInitialize_AOEnter
                    section.data(17).logicalSrcIdx = 54;
                    section.data(17).dtTransOffset = 16;

                    ;% Simulink_P.HILInitialize_AOReset
                    section.data(18).logicalSrcIdx = 55;
                    section.data(18).dtTransOffset = 17;

                    ;% Simulink_P.HILInitialize_DOPStart
                    section.data(19).logicalSrcIdx = 56;
                    section.data(19).dtTransOffset = 18;

                    ;% Simulink_P.HILInitialize_DOPEnter
                    section.data(20).logicalSrcIdx = 57;
                    section.data(20).dtTransOffset = 19;

                    ;% Simulink_P.HILInitialize_DOStart
                    section.data(21).logicalSrcIdx = 58;
                    section.data(21).dtTransOffset = 20;

                    ;% Simulink_P.HILInitialize_DOEnter
                    section.data(22).logicalSrcIdx = 59;
                    section.data(22).dtTransOffset = 21;

                    ;% Simulink_P.HILInitialize_DOReset
                    section.data(23).logicalSrcIdx = 60;
                    section.data(23).dtTransOffset = 22;

                    ;% Simulink_P.HILInitialize_EIPStart
                    section.data(24).logicalSrcIdx = 61;
                    section.data(24).dtTransOffset = 23;

                    ;% Simulink_P.HILInitialize_EIPEnter
                    section.data(25).logicalSrcIdx = 62;
                    section.data(25).dtTransOffset = 24;

                    ;% Simulink_P.HILInitialize_EIStart
                    section.data(26).logicalSrcIdx = 63;
                    section.data(26).dtTransOffset = 25;

                    ;% Simulink_P.HILInitialize_EIEnter
                    section.data(27).logicalSrcIdx = 64;
                    section.data(27).dtTransOffset = 26;

                    ;% Simulink_P.HILInitialize_POPStart
                    section.data(28).logicalSrcIdx = 65;
                    section.data(28).dtTransOffset = 27;

                    ;% Simulink_P.HILInitialize_POPEnter
                    section.data(29).logicalSrcIdx = 66;
                    section.data(29).dtTransOffset = 28;

                    ;% Simulink_P.HILInitialize_POStart
                    section.data(30).logicalSrcIdx = 67;
                    section.data(30).dtTransOffset = 29;

                    ;% Simulink_P.HILInitialize_POEnter
                    section.data(31).logicalSrcIdx = 68;
                    section.data(31).dtTransOffset = 30;

                    ;% Simulink_P.HILInitialize_POReset
                    section.data(32).logicalSrcIdx = 69;
                    section.data(32).dtTransOffset = 31;

                    ;% Simulink_P.HILInitialize_OOReset
                    section.data(33).logicalSrcIdx = 70;
                    section.data(33).dtTransOffset = 32;

                    ;% Simulink_P.HILInitialize_DOFinal
                    section.data(34).logicalSrcIdx = 71;
                    section.data(34).dtTransOffset = 33;

                    ;% Simulink_P.HILInitialize_DOInitial
                    section.data(35).logicalSrcIdx = 72;
                    section.data(35).dtTransOffset = 34;

                    ;% Simulink_P.HILReadEncoderTimebase_Active
                    section.data(36).logicalSrcIdx = 73;
                    section.data(36).dtTransOffset = 35;

                    ;% Simulink_P.HILWriteAnalog_Active
                    section.data(37).logicalSrcIdx = 74;
                    section.data(37).dtTransOffset = 36;

                    ;% Simulink_P.HILRead_Active
                    section.data(38).logicalSrcIdx = 75;
                    section.data(38).dtTransOffset = 37;

            nTotData = nTotData + section.nData;
            paramMap.sections(5) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Simulink_P.HILReadEncoderTimebase_Overflow
                    section.data(1).logicalSrcIdx = 76;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            paramMap.sections(6) = section;
            clear section


            ;%
            ;% Non-auto Data (parameter)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        paramMap.nTotData = nTotData;



    ;%**************************
    ;% Create Block Output Map *
    ;%**************************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 1;
        sectIdxOffset = 0;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc sigMap
        ;%
        sigMap.nSections           = nTotSects;
        sigMap.sectIdxOffset       = sectIdxOffset;
            sigMap.sections(nTotSects) = dumSection; %prealloc
        sigMap.nTotData            = -1;

        ;%
        ;% Auto data (Simulink_B)
        ;%
            section.nData     = 7;
            section.data(7)  = dumData; %prealloc

                    ;% Simulink_B.Gain1
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% Simulink_B.Derivative
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 1;

                    ;% Simulink_B.DerivLPF
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 2;

                    ;% Simulink_B.LPF
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 3;

                    ;% Simulink_B.Realspeed
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 4;

                    ;% Simulink_B.Gain2
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 5;

                    ;% Simulink_B.Derivative1
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 6;

            nTotData = nTotData + section.nData;
            sigMap.sections(1) = section;
            clear section


            ;%
            ;% Non-auto Data (signal)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        sigMap.nTotData = nTotData;



    ;%*******************
    ;% Create DWork Map *
    ;%*******************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 6;
        sectIdxOffset = 1;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc dworkMap
        ;%
        dworkMap.nSections           = nTotSects;
        dworkMap.sectIdxOffset       = sectIdxOffset;
            dworkMap.sections(nTotSects) = dumSection; %prealloc
        dworkMap.nTotData            = -1;

        ;%
        ;% Auto data (Simulink_DW)
        ;%
            section.nData     = 16;
            section.data(16)  = dumData; %prealloc

                    ;% Simulink_DW.HILInitialize_AIMinimums
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% Simulink_DW.HILInitialize_AIMaximums
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 2;

                    ;% Simulink_DW.HILInitialize_AOMinimums
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 4;

                    ;% Simulink_DW.HILInitialize_AOMaximums
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 6;

                    ;% Simulink_DW.HILInitialize_AOVoltages
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 8;

                    ;% Simulink_DW.HILInitialize_FilterFrequency
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 10;

                    ;% Simulink_DW.HILWriteAnalog_Buffer
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 14;

                    ;% Simulink_DW.TimeStampA
                    section.data(8).logicalSrcIdx = 7;
                    section.data(8).dtTransOffset = 16;

                    ;% Simulink_DW.LastUAtTimeA
                    section.data(9).logicalSrcIdx = 8;
                    section.data(9).dtTransOffset = 17;

                    ;% Simulink_DW.TimeStampB
                    section.data(10).logicalSrcIdx = 9;
                    section.data(10).dtTransOffset = 18;

                    ;% Simulink_DW.LastUAtTimeB
                    section.data(11).logicalSrcIdx = 10;
                    section.data(11).dtTransOffset = 19;

                    ;% Simulink_DW.HILRead_OtherBuffer
                    section.data(12).logicalSrcIdx = 11;
                    section.data(12).dtTransOffset = 20;

                    ;% Simulink_DW.TimeStampA_o
                    section.data(13).logicalSrcIdx = 12;
                    section.data(13).dtTransOffset = 21;

                    ;% Simulink_DW.LastUAtTimeA_k
                    section.data(14).logicalSrcIdx = 13;
                    section.data(14).dtTransOffset = 22;

                    ;% Simulink_DW.TimeStampB_g
                    section.data(15).logicalSrcIdx = 14;
                    section.data(15).dtTransOffset = 23;

                    ;% Simulink_DW.LastUAtTimeB_o
                    section.data(16).logicalSrcIdx = 15;
                    section.data(16).dtTransOffset = 24;

            nTotData = nTotData + section.nData;
            dworkMap.sections(1) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Simulink_DW.HILInitialize_Card
                    section.data(1).logicalSrcIdx = 16;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(2) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Simulink_DW.HILReadEncoderTimebase_Task
                    section.data(1).logicalSrcIdx = 17;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(3) = section;
            clear section

            section.nData     = 3;
            section.data(3)  = dumData; %prealloc

                    ;% Simulink_DW.HILWriteAnalog_PWORK
                    section.data(1).logicalSrcIdx = 18;
                    section.data(1).dtTransOffset = 0;

                    ;% Simulink_DW.HILRead_PWORK
                    section.data(2).logicalSrcIdx = 19;
                    section.data(2).dtTransOffset = 1;

                    ;% Simulink_DW.Speedestimation_PWORK.LoggedData
                    section.data(3).logicalSrcIdx = 20;
                    section.data(3).dtTransOffset = 2;

            nTotData = nTotData + section.nData;
            dworkMap.sections(4) = section;
            clear section

            section.nData     = 5;
            section.data(5)  = dumData; %prealloc

                    ;% Simulink_DW.HILInitialize_ClockModes
                    section.data(1).logicalSrcIdx = 21;
                    section.data(1).dtTransOffset = 0;

                    ;% Simulink_DW.HILInitialize_DOStates
                    section.data(2).logicalSrcIdx = 22;
                    section.data(2).dtTransOffset = 1;

                    ;% Simulink_DW.HILInitialize_QuadratureModes
                    section.data(3).logicalSrcIdx = 23;
                    section.data(3).dtTransOffset = 3;

                    ;% Simulink_DW.HILInitialize_InitialEICounts
                    section.data(4).logicalSrcIdx = 24;
                    section.data(4).dtTransOffset = 7;

                    ;% Simulink_DW.HILReadEncoderTimebase_Buffer
                    section.data(5).logicalSrcIdx = 25;
                    section.data(5).dtTransOffset = 11;

            nTotData = nTotData + section.nData;
            dworkMap.sections(5) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Simulink_DW.HILInitialize_DOBits
                    section.data(1).logicalSrcIdx = 26;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(6) = section;
            clear section


            ;%
            ;% Non-auto Data (dwork)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        dworkMap.nTotData = nTotData;



    ;%
    ;% Add individual maps to base struct.
    ;%

    targMap.paramMap  = paramMap;
    targMap.signalMap = sigMap;
    targMap.dworkMap  = dworkMap;

    ;%
    ;% Add checksums to base struct.
    ;%


    targMap.checksum0 = 208607193;
    targMap.checksum1 = 2410890202;
    targMap.checksum2 = 2172331919;
    targMap.checksum3 = 1432870620;

