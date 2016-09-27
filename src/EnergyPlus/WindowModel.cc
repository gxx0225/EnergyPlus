#include "InputProcessor.hh"
#include "DataIPShortCuts.hh"

#include "WindowModel.hh"

using namespace std;

namespace EnergyPlus {  

  template<>
  EnumParser< EnergyPlus::WindowManager::WindowsModel >::EnumParser() {
    m_Map[ "BUILTINWINDOWSMODEL" ] = WindowManager::WindowsModel::BuiltIn;
    m_Map[ "EXTERNALWINDOWSMODEL" ] = WindowManager::WindowsModel::External;
  }

  namespace WindowManager {

    /////////////////////////////////////////////////////////////////////////////////////////
    //  CWindowModel
    /////////////////////////////////////////////////////////////////////////////////////////

    CWindowModel::CWindowModel() : m_Model( WindowsModel::BuiltIn ) {

    }
  

    shared_ptr< CWindowModel > CWindowModel::WindowModelFactory( string objectName ) {
      // SUBROUTINE INFORMATION:
      //       AUTHOR         Simon Vidanovic
      //       DATE WRITTEN   July 2016
      //       MODIFIED       na
      //       RE-ENGINEERED  na

      using namespace DataIPShortCuts;

      // PURPOSE OF THIS SUBROUTINE:
      // Reads input and creates instance of WindowModel object
      int NumNums;
      int NumAlphas;
      int IOStat;

      shared_ptr< CWindowModel > aModel = make_shared< CWindowModel >();
      int numCurrModels = InputProcessor::GetNumObjectsFound( objectName );
      if( numCurrModels > 0 ) {
        InputProcessor::GetObjectItem( objectName, 1, cAlphaArgs, NumAlphas, rNumericArgs, NumNums, IOStat );
        EnumParser< WindowsModel > aParser;
        aModel->m_Model = aParser.StringToEnum( cAlphaArgs( 1 ) );
      }

      return aModel;
    }

    WindowsModel CWindowModel::getWindowsModel() const {
      return m_Model;
    }

    bool CWindowModel::isExternalLibraryModel() const {
      return m_Model == WindowsModel::External;
    }

  }


}