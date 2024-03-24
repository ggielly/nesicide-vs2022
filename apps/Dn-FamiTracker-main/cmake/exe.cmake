include_directories(.)
include_directories(Source)

add_executable(${exe}
        WIN32

        res/About.bmp
        res/Application.ico
        res/Document.ico
        res/Inst_2A03.ico
        res/Inst_2A07.ico
        res/Inst_FDS.ico
        res/Inst_N163.ico
        res/Inst_S5B.ico
        res/Inst_VRC6.ico
        res/Inst_VRC7.ico
        res/InstrumentToolbar-16.bmp
        res/InstrumentToolbar-256.bmp
        res/key_black_pressed.bmp
        res/key_black_unpressed.bmp
        res/key_white_pressed.bmp
        res/key_white_unpressed.bmp
        res/LeftArrow.ico
        res/MainToolbar-16.bmp
        res/MainToolbar-256.bmp
        res/RightArrow.ico

        # Resources
        # To avoid duplicate manifest linking errors, do NOT include
        # res/Dn-FamiTracker.manifest!
        Dn-FamiTracker.rc
        resource.h

        # Global headers
        name.h
        version.h

        # Emulator cores
        Source/APU/digital-sound-antiques/2413tone.h
        Source/APU/digital-sound-antiques/281btone.h
        Source/APU/digital-sound-antiques/emu2413.c
        Source/APU/digital-sound-antiques/emu2413.h
        Source/APU/digital-sound-antiques/vrc7tone_ft35.h
        Source/APU/digital-sound-antiques/vrc7tone_ft36.h
        Source/APU/digital-sound-antiques/vrc7tone_kt1.h
        Source/APU/digital-sound-antiques/vrc7tone_kt2.h
        Source/APU/digital-sound-antiques/vrc7tone_mo.h
        Source/APU/digital-sound-antiques/vrc7tone_nuke.h
        Source/APU/digital-sound-antiques/vrc7tone_rw.h

        Source/APU/mesen/BaseFdsChannel.h
        Source/APU/mesen/FdsAudio.h
        Source/APU/mesen/ModChannel.h
        Source/APU/mesen/Namco163Audio.h

        Source/APU/nsfplay/xgm/debugout.h
        Source/APU/nsfplay/xgm/xtypes.h
        Source/APU/nsfplay/xgm/devices/device.h
        Source/APU/nsfplay/xgm/devices/devinfo.h
        Source/APU/nsfplay/xgm/devices/CPU/nes_cpu.h
        Source/APU/nsfplay/xgm/devices/Sound/nsfplay_math.h
        Source/APU/nsfplay/xgm/devices/Sound/nes_apu.cpp
        Source/APU/nsfplay/xgm/devices/Sound/nes_apu.h
        Source/APU/nsfplay/xgm/devices/Sound/nes_dmc.cpp
        Source/APU/nsfplay/xgm/devices/Sound/nes_dmc.h

        # Libraries
        Source/Blip_Buffer/Blip_Buffer.cpp
        Source/Blip_Buffer/Blip_Buffer.h

        Source/FFT/FftBuffer.h
        Source/FFT/FftComplex.hpp

        Source/gsl/gsl
        Source/gsl/gsl_algorithm
        Source/gsl/gsl_assert
        Source/gsl/gsl_byte
        Source/gsl/gsl_util
        Source/gsl/multi_span
        Source/gsl/pointers
        Source/gsl/span
        Source/gsl/span_ext
        Source/gsl/string_span

        Source/json/json.hpp

        Source/resampler/resample.cpp
        Source/resampler/resample.hpp
        Source/resampler/resample.inl
        Source/resampler/sinc.cpp
        Source/resampler/sinc.hpp

        Source/rigtorp/SPSCQueue.h

        Source/str_conv/str_conv.hpp
        Source/str_conv/utf8_conv.hpp

        Source/type_safe/arithmetic_policy.hpp
        Source/type_safe/boolean.hpp
        Source/type_safe/bounded_type.hpp
        Source/type_safe/compact_optional.hpp
        Source/type_safe/config.hpp
        Source/type_safe/constrained_type.hpp
        Source/type_safe/deferred_construction.hpp
        Source/type_safe/detail/aligned_union.hpp
        Source/type_safe/detail/all_of.hpp
        Source/type_safe/detail/assert.hpp
        Source/type_safe/detail/assign_or_construct.hpp
        Source/type_safe/detail/constant_parser.hpp
        Source/type_safe/detail/copy_move_control.hpp
        Source/type_safe/detail/force_inline.hpp
        Source/type_safe/detail/is_nothrow_swappable.hpp
        Source/type_safe/detail/map_invoke.hpp
        Source/type_safe/detail/variant_impl.hpp
        Source/type_safe/downcast.hpp
        Source/type_safe/flag.hpp
        Source/type_safe/flag_set.hpp
        Source/type_safe/floating_point.hpp
        Source/type_safe/index.hpp
        Source/type_safe/integer.hpp
        Source/type_safe/narrow_cast.hpp
        Source/type_safe/optional.hpp
        Source/type_safe/optional_ref.hpp
        Source/type_safe/output_parameter.hpp
        Source/type_safe/reference.hpp
        Source/type_safe/strong_typedef.hpp
        Source/type_safe/tagged_union.hpp
        Source/type_safe/types.hpp
        Source/type_safe/variant.hpp
        Source/type_safe/visitor.hpp

        Source/WinSDK/VersionHelpers.h
        Source/WinSDK/winapifamily.h

        # NSF driver binaries
        Source/drivers/drv_2a03.h
        Source/drivers/drv_all.h
        Source/drivers/drv_fds.h
        Source/drivers/drv_mmc5.h
        Source/drivers/drv_n163.h
        Source/drivers/drv_s5b.h
        Source/drivers/drv_vrc6.h
        Source/drivers/drv_vrc7.h

        # Utilities
        Source/utils/ftmath.cpp
        Source/utils/ftmath.h
        Source/utils/handle_ptr.h
        Source/utils/input.h
        Source/utils/variadic_minmax.h

        # Sources
        Source/APU/2A03.cpp
        Source/APU/2A03.h
        Source/APU/2A03Chan.h
        Source/APU/APU.cpp
        Source/APU/APU.h
        Source/APU/Channel.h
        Source/APU/ChannelLevelState.h
        Source/APU/FDS.cpp
        Source/APU/FDS.h
        Source/APU/Mixer.cpp
        Source/APU/Mixer.h
        Source/APU/MMC5.cpp
        Source/APU/MMC5.h
        Source/APU/N163.cpp
        Source/APU/N163.h
        Source/APU/S5B.cpp
        Source/APU/S5B.h
        Source/APU/SoundChip.cpp
        Source/APU/SoundChip.h
        Source/APU/SoundChip2.cpp
        Source/APU/SoundChip2.h
        Source/APU/Square.cpp
        Source/APU/Square.h
        Source/APU/Types.h
        Source/APU/VRC6.cpp
        Source/APU/VRC6.h
        Source/APU/VRC7.cpp
        Source/APU/VRC7.h
		
        Source/AboutDlg.cpp
        Source/AboutDlg.h
        Source/Accelerator.cpp
        Source/Accelerator.h
        Source/Action.cpp
        Source/Action.h
        Source/Bookmark.cpp
        Source/Bookmark.h
        Source/BookmarkCollection.cpp
        Source/BookmarkCollection.h
        Source/BookmarkDlg.cpp
        Source/BookmarkDlg.h
        Source/BookmarkManager.cpp
        Source/BookmarkManager.h
        Source/ChannelFactory.cpp
        Source/ChannelFactory.h
        Source/ChannelHandler.cpp
        Source/ChannelHandler.h
        Source/ChannelHandlerInterface.h
        Source/ChannelMap.cpp
        Source/ChannelMap.h
        Source/Channels2A03.cpp
        Source/Channels2A03.h
        Source/ChannelsDlg.cpp
        Source/ChannelsDlg.h
        Source/ChannelsFDS.cpp
        Source/ChannelsFDS.h
        Source/ChannelsMMC5.cpp
        Source/ChannelsMMC5.h
        Source/ChannelsN163.cpp
        Source/ChannelsN163.h
        Source/ChannelsS5B.cpp
        Source/ChannelsS5B.h
        Source/ChannelState.cpp
        Source/ChannelState.h
        Source/ChannelsVRC6.cpp
        Source/ChannelsVRC6.h
        Source/ChannelsVRC7.cpp
        Source/ChannelsVRC7.h
        Source/Chunk.cpp
        Source/Chunk.h
        Source/ChunkRenderBinary.cpp
        Source/ChunkRenderBinary.h
        Source/ChunkRenderText.cpp
        Source/ChunkRenderText.h
        Source/Clipboard.cpp
        Source/Clipboard.h
        Source/ColorScheme.h
        Source/CommandLineExport.cpp
        Source/CommandLineExport.h
        Source/CommentsDlg.cpp
        Source/CommentsDlg.h
        Source/Common.h
        Source/Compiler.cpp
        Source/Compiler.h
        Source/CompoundAction.cpp
        Source/CompoundAction.h
        Source/ConfigAppearance.cpp
        Source/ConfigAppearance.h
        Source/ConfigEmulation.cpp
        Source/ConfigEmulation.h
        Source/ConfigGeneral.cpp
        Source/ConfigGeneral.h
        Source/ConfigGUI.cpp
        Source/ConfigGUI.h
        Source/ConfigMIDI.cpp
        Source/ConfigMIDI.h
        Source/ConfigMixer.cpp
        Source/ConfigMixer.h
        Source/ConfigShortcuts.cpp
        Source/ConfigShortcuts.h
        Source/ConfigSound.cpp
        Source/ConfigSound.h
        Source/ConfigVersion.cpp
        Source/ConfigVersion.h
        Source/ConfigWindow.cpp
        Source/ConfigWindow.h
        Source/ControlPanelDlg.cpp
        Source/ControlPanelDlg.h
        Source/CreateWaveDlg.cpp
        Source/CreateWaveDlg.h
        Source/CustomControls.cpp
        Source/CustomControls.h
        Source/CustomExporter.cpp
        Source/CustomExporter.h
        Source/CustomExporterInterfaces.h
        Source/CustomExporters.cpp
        Source/CustomExporters.h
        Source/CustomExporter_C_Interface.cpp
        Source/CustomExporter_C_Interface.h
        Source/DetuneDlg.cpp
        Source/DetuneDlg.h
        Source/DetuneTable.cpp
        Source/DetuneTable.h
        Source/DialogReBar.cpp
        Source/DialogReBar.h
        Source/DocumentFile.cpp
        Source/DocumentFile.h
        Source/DocumentWrapper.cpp
        Source/DocumentWrapper.h
        Source/DPI.cpp
        Source/DPI.h
        Source/Driver.h
        Source/DSample.cpp
        Source/DSample.h
        Source/DSampleManager.cpp
        Source/DSampleManager.h
        Source/Exception.cpp
        Source/Exception.h
        Source/ExportDialog.cpp
        Source/ExportDialog.h
        Source/Factory.h
        Source/FamiTracker.cpp
        Source/FamiTracker.h
        Source/FamiTrackerDoc.cpp
        Source/FamiTrackerDoc.h
        Source/FamiTrackerTypes.cpp
        Source/FamiTrackerTypes.h
        Source/FamiTrackerView.cpp
        Source/FamiTrackerView.h
        Source/FamiTrackerViewMessage.h
        Source/FindDlg.cpp
        Source/FindDlg.h
        Source/FrameAction.cpp
        Source/FrameAction.h
        Source/FrameEditor.cpp
        Source/FrameEditor.h
        Source/FrameEditorTypes.cpp
        Source/FrameEditorTypes.h
        Source/FTMComponentInterface.h
        Source/GotoDlg.cpp
        Source/GotoDlg.h
        Source/GraphEditor.cpp
        Source/GraphEditor.h
        Source/Graphics.cpp
        Source/Graphics.h
        Source/Groove.cpp
        Source/Groove.h
        Source/GrooveDlg.cpp
        Source/GrooveDlg.h
        Source/HistoryFileDlg.cpp
        Source/HistoryFileDlg.h
        Source/InstHandler.h
        Source/InstHandlerDPCM.cpp
        Source/InstHandlerDPCM.h
        Source/InstHandlerVRC7.cpp
        Source/InstHandlerVRC7.h
        Source/Instrument.cpp
        Source/Instrument.h
        Source/Instrument2A03.cpp
        Source/Instrument2A03.h
        Source/InstrumentEditDlg.cpp
        Source/InstrumentEditDlg.h
        Source/InstrumentEditorDPCM.cpp
        Source/InstrumentEditorDPCM.h
        Source/InstrumentEditorFDS.cpp
        Source/InstrumentEditorFDS.h
        Source/InstrumentEditorFDSEnvelope.cpp
        Source/InstrumentEditorFDSEnvelope.h
        Source/InstrumentEditorN163Wave.cpp
        Source/InstrumentEditorN163Wave.h
        Source/InstrumentEditorSeq.cpp
        Source/InstrumentEditorSeq.h
        Source/InstrumentEditorVRC7.cpp
        Source/InstrumentEditorVRC7.h
        Source/InstrumentEditPanel.cpp
        Source/InstrumentEditPanel.h
        Source/InstrumentFactory.cpp
        Source/InstrumentFactory.h
        Source/InstrumentFDS.cpp
        Source/InstrumentFDS.h
        Source/InstrumentFileTree.cpp
        Source/InstrumentFileTree.h
        Source/InstrumentListCtrl.cpp
        Source/InstrumentManager.cpp
        Source/InstrumentManager.h
        Source/InstrumentManagerInterface.h
        Source/InstrumentN163.cpp
        Source/InstrumentN163.h
        Source/InstrumentRecorder.cpp
        Source/InstrumentRecorder.h
        Source/InstrumentS5B.cpp
        Source/InstrumentS5B.h
        Source/InstrumentVRC6.cpp
        Source/InstrumentVRC6.h
        Source/InstrumentVRC7.cpp
        Source/InstrumentVRC7.h
        Source/IntRange.h
        Source/MainFrm.cpp
        Source/MainFrm.h
        Source/MIDI.cpp
        Source/MIDI.h
        Source/ModSequenceEditor.cpp
        Source/ModSequenceEditor.h
        Source/ModuleException.cpp
        Source/ModuleException.h
        Source/ModuleImportDlg.cpp
        Source/ModuleImportDlg.h
        Source/ModulePropertiesDlg.cpp
        Source/ModulePropertiesDlg.h
        Source/NoNotifyEdit.cpp
        Source/NoNotifyEdit.h
        Source/NoteQueue.cpp
        Source/NoteQueue.h
        Source/NumConv.h
        Source/OldSequence.cpp
        Source/OldSequence.h
        Source/PatternAction.cpp
        Source/PatternAction.h
        Source/PatternCompiler.cpp
        Source/PatternCompiler.h
        Source/PatternComponent.cpp
        Source/PatternComponent.h
        Source/PatternData.cpp
        Source/PatternData.h
        Source/PatternEditor.cpp
        Source/PatternEditor.h
        Source/PatternEditorTypes.cpp
        Source/PatternEditorTypes.h
        Source/PatternNote.cpp
        Source/PatternNote.h
        Source/PCMImport.cpp
        Source/PCMImport.h
        Source/PerformanceDlg.cpp
        Source/PerformanceDlg.h
        Source/RecordSettingsDlg.cpp
        Source/RecordSettingsDlg.h
        Source/RegisterState.cpp
        Source/RegisterState.h
        Source/SampleEditorDlg.cpp
        Source/SampleEditorDlg.h
        Source/SampleEditorView.cpp
        Source/SampleEditorView.h
        Source/SeqInstHandler.cpp
        Source/SeqInstHandler.h
        Source/SeqInstHandler2A03Pulse.cpp
        Source/SeqInstHandler2A03Pulse.h
        Source/SeqInstHandlerFDS.cpp
        Source/SeqInstHandlerFDS.h
        Source/SeqInstHandlerN163.cpp
        Source/SeqInstHandlerN163.h
        Source/SeqInstHandlerS5B.cpp
        Source/SeqInstHandlerS5B.h
        Source/SeqInstHandlerSawtooth.cpp
        Source/SeqInstHandlerSawtooth.h
        Source/SeqInstrument.cpp
        Source/SeqInstrument.h
        Source/Sequence.cpp
        Source/Sequence.h
        Source/SequenceCollection.cpp
        Source/SequenceCollection.h
        Source/SequenceEditor.cpp
        Source/SequenceEditor.h
        Source/SequenceEditorMessage.h
        Source/SequenceManager.cpp
        Source/SequenceManager.h
        Source/SequenceParser.cpp
        Source/SequenceParser.h
        Source/SequenceSetting.cpp
        Source/SequenceSetting.h
        Source/Settings.cpp
        Source/Settings.h
        Source/SimpleFile.cpp
        Source/SimpleFile.h
        Source/SizeEditor.cpp
        Source/SizeEditor.h
        Source/SoundGen.cpp
        Source/SoundGen.h
        Source/SoundInterface.cpp
        Source/SoundInterface.h
        Source/SpeedDlg.cpp
        Source/SpeedDlg.h
        Source/SplitKeyboardDlg.cpp
        Source/SplitKeyboardDlg.h
        Source/stdafx.cpp
        Source/stdafx.h
        Source/StretchDlg.cpp
        Source/StretchDlg.h
        Source/SwapDlg.cpp
        Source/SwapDlg.h
        Source/TextExporter.cpp
        Source/TextExporter.h
        Source/to_sv.h
        Source/TrackerChannel.cpp
        Source/TrackerChannel.h
        Source/TransposeDlg.cpp
        Source/TransposeDlg.h
        Source/VersionChecker.cpp
        Source/VersionChecker.h
        Source/VersionCheckerDlg.cpp
        Source/VersionCheckerDlg.h
        Source/VisualizerBase.cpp
        Source/VisualizerBase.h
        Source/VisualizerScope.cpp
        Source/VisualizerScope.h
        Source/VisualizerSpectrum.cpp
        Source/VisualizerSpectrum.h
        Source/VisualizerStatic.cpp
        Source/VisualizerStatic.h
        Source/VisualizerWnd.cpp
        Source/VisualizerWnd.h
        Source/WaveEditor.cpp
        Source/WaveEditor.h
        Source/WaveFile.cpp
        Source/WaveFile.h
        Source/WaveformGenerator.cpp
        Source/WaveformGenerator.h
        Source/WavegenBuiltin.cpp
        Source/WavegenBuiltin.h
        Source/WavProgressDlg.cpp
        Source/WavProgressDlg.h
        )