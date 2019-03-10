pipeline {
    agent any

    stages {

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
                dir('build')
                {
                    sh 'cmake3 ..'
                    sh 'make'
                }
            }
        }
    }
}
