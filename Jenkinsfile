pipeline {
    agent any

    environment {
       CXX = "g++-4.9.4"
       LD = "g++-4.9.4"
       ETL_MKL = 'true'
    }

    stages {
        stage ('checkout'){
            steps {
                checkout([
                    $class: 'GitSCM',
                    branches: scm.branches,
                    doGenerateSubmoduleConfigurations: false,
                    extensions: scm.extensions + [[$class: 'SubmoduleOption', disableSubmodules: false, recursiveSubmodules: true, reference: '', trackingSubmodules: false]],
                    submoduleCfg: [],
                    userRemoteConfigs: scm.userRemoteConfigs])
            }
        }

        stage ('pre-analysis') {
            steps {
                //sh 'cppcheck --xml-version=2 -j3 --enable=all --std=c++11 `git ls-files "*.hpp" "*.cpp"` 2> cppcheck_report.xml'
                sh 'cppcheck --enable=warning,performance,portability,information,missingInclude \
                    --std=c++11 --library=qt.cfg --verbose --quiet \
                    --template="[{severity}][{id}] {message} {callstack} (On {file}:{line})" \
                    `git ls-files "*.hpp" "*.cpp"` '
            }
        }

        stage ('build'){
            steps {
                sh 'cmake -G "Unix Makefiles" .'
            }
        }
    }
}
